# EncoderInterfaceSimple

Authors:

    Peter Polidoro <polidorop@janelia.hhmi.org>

License:

    BSD

## Ancestors

[ModularServer](https://github.com/janelia-arduino/ModularServer)

[ModularDeviceBase](https://github.com/janelia-arduino/ModularDeviceBase)

## Clients

## Devices

[modular_device_base](https://github.com/janelia-modular-devices/modular_device_base.git)

[encoder_interface_simple](https://github.com/janelia-modular-devices/encoder_interface_simple.git)

## API

```json
{
  "id":"getApi",
  "result":{
    "firmware":["EncoderInterfaceSimple"],
    "functions":[
      "enableAllOutputs",
      "disableAllOutputs",
      "outputsEnabled",
      "getPositions",
      "setPosition"
    ],
    "parameters":[
      "encoder_index",
      "position"
    ],
    "properties":[
      "invertEncoderDirection"
    ],
    "callbacks":[]
  }
}
```

## API Verbose

[API Verbose](./api.json)

## More Detailed Modular Device Information

[modular-devices](https://github.com/janelia-modular-devices/modular-devices)

## Install Library Dependencies

[arduino-libraries](https://github.com/janelia-arduino/arduino-libraries)
