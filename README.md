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
    "properties":[],
    "callbacks":[]
  }
}
```

## API Verbose

```json
{
  "id":"getApiVerbose",
  "result":{
    "firmware":["EncoderInterfaceSimple"],
    "functions":[
      {
        "name":"enableAllOutputs",
        "parameters":[]
      },
      {
        "name":"disableAllOutputs",
        "parameters":[]
      },
      {
        "name":"outputsEnabled",
        "parameters":[],
        "result_info":{
          "type":"bool"
        }
      },
      {
        "name":"getPositions",
        "parameters":[],
        "result_info":{
          "type":"array",
          "array_element_type":"long"
        }
      },
      {
        "name":"setPosition",
        "parameters":[
          "encoder_index",
          "position"
        ]
      }
    ],
    "parameters":[
      {
        "name":"encoder_index",
        "type":"long"
      },
      {
        "name":"position",
        "type":"long"
      }
    ],
    "properties":[],
    "callbacks":[]
  }
}
```

## More Detailed Modular Device Information

[modular-devices](https://github.com/janelia-modular-devices/modular-devices)

## Install Library Dependencies

[arduino-libraries](https://github.com/janelia-arduino/arduino-libraries)
