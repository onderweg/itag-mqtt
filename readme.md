# iTag to MQTT

Publish iTag button press notifications to MQTT queue.

*work in progress*

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