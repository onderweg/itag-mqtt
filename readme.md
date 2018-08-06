# iTag to MQTT

*work in progress*

Publish iTag button press notifications to MQTT queue.

An iTag is cheap (< 2 euro) BLE device equipped with button and piezzo buzzer. This program listens to button
press notifications, and publishes a message to a MQTT queue on press.

## Build

Requirements:

- gcc
- [GattLib](https://github.com/labapart/gattlib) (lgattlib)
- GLib 
- Paho MQTT C Client (lpaho-mqtt3c)

Build:

```
$ make
```

Note: since GattLib is a dependency, you can only build on Linux.

## Run

```
./button <MAC ADDR OF BUTTON>
```

## References

- [About bluetooth tracking tags](https://github.com/sputnikdev/eclipse-smarthome-bluetooth-binding/blob/master/tags.md)
- [Gatttool : Analyse du porte-clefs iTAG](https://www.fanjoe.be/?p=2861)