# iTag to MQTT

*work in progress*

Publish iTag button press notifications to MQTT queue.

An iTag is cheap (< 2 euro) BLE device equipped with button and piezzo buzzer. This program listens to button
press notifications, and publishes a message to a MQTT queue on press.

## Build

Requirements:

- gcc
- [GattLib](https://github.com/labapart/gattlib) (lgattlib)
- GLib (lglib-2.0)
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

## Working with iTag buttons

Although iTags seem perfect to use as a smart button in home automation applications, especially because of their low price, there are some big caveats.

- Connection behaviour is erratic. Often difficult to reconnect after disconnection.
- Range is limited.
- Beeping on button press and connection loss is annoying. No known way of disabling these beeps.

They are perfect though for experimenting with Bluetooth Low Energy devices and the GATT protocol.

And, I should mention that iTags are not designed to be used as a smart button, their intended use is as a tracking device, to help you find your keys for example.
 
## References

- [About bluetooth tracking tags](https://github.com/sputnikdev/eclipse-smarthome-bluetooth-binding/blob/master/tags.md)
- [Gatttool : Analyse du porte-clefs iTAG](https://www.fanjoe.be/?p=2861)
