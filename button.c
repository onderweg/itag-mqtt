#include "MQTTClient.h"
#include "gattlib.h"
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MQTT_TOPIC_TEMP_FMT "home/buttons/itag/%s"
#define MQTT_HOST "localhost"

const uuid_t g_click_notify_uuid = CREATE_UUID16(0xffe1);
GMainLoop *loop;
gatt_connection_t *connection;
char *addr;

int mqtt_publish() {
  // MQTT Client setup
  MQTTClient client;
  MQTTClient_create(&client, MQTT_HOST, "C-CLIENT", MQTTCLIENT_PERSISTENCE_NONE,
                    NULL);
  MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
  conn_opts.keepAliveInterval = 20;
  int rc;
  if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS) {
    printf("Failed to connect to MQTT server, return code %d\n", rc);
    return rc;
  }

  // Publish message
  char *topic = g_strdup_printf(MQTT_TOPIC_TEMP_FMT, addr);
  char *payload = "click";
  MQTTClient_message pubmsg = MQTTClient_message_initializer;
  pubmsg.payload = payload;
  pubmsg.payloadlen = strlen(pubmsg.payload);
  pubmsg.qos = 2;
  pubmsg.retained = 1;
  MQTTClient_deliveryToken token;
  MQTTClient_publishMessage(client, topic, &pubmsg, &token);
  MQTTClient_waitForCompletion(client, token, 1000L);
  printf("MQTT Message '%s' delivered to topic: %s\n", payload, topic);

  // Cleanup
  MQTTClient_disconnect(client, 1000);
  MQTTClient_destroy(&client);
  return rc;
}

void notification_handler(const uuid_t *uuid,
                          const uint8_t *data,
                          size_t data_length,
                          void *user_data) {
  printf("Click notification received. Data: ");
  int i;
  for (i = 0; i < data_length; i++) {
    printf("%02x ", data[i]);
  }
  printf("\n");
  mqtt_publish();
}

static void usage(char *argv[]) {
  printf("Usage: %s <device_address>\n", argv[0]);
}

void ctrlc_handler(int signal) {
  g_main_loop_quit(loop);
}

int connect_device(char *deviceAddr) {
  int attempt = 1;
  do {
    printf("Connection attempt %d\n", attempt);
    connection =
        gattlib_connect(NULL, deviceAddr, BDADDR_LE_PUBLIC, BT_SEC_LOW, 0, 0);
    if (connection == NULL) {
      printf("Failed to connect to the bluetooth device [%s]\n", addr);
      sleep(3);
    }
  } while (connection == NULL && ++attempt <= 3);
  return (connection == NULL);
}

int start_listener() {
  gattlib_register_notification(connection, notification_handler, NULL);
  int ret = gattlib_notification_start(connection, &g_click_notify_uuid);
  return ret;
}

int main(int argc, char *argv[]) {
  int ret;
  char uuid_str[64];

  if (argc != 2) {
    usage(argv);
    return 1;
  }
  addr = argv[1];

  ret = connect_device(addr);
  if (ret) {
    return ret;
  }

  signal(SIGINT, ctrlc_handler);

  gattlib_uuid_to_string(&g_click_notify_uuid, uuid_str, sizeof(uuid_str));

  ret = start_listener();
  if (ret) {
    printf("Failed to start notification for UUID %s\n", uuid_str);
    return 1;
  }
  printf("Notifications started for UUID %s\n", uuid_str);

  loop = g_main_loop_new(NULL, 0);

  g_main_loop_run(loop);

  g_main_loop_unref(loop);
  gattlib_disconnect(connection);

  puts("Disconnected");
  return 0;
}