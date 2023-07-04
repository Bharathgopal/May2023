# Packet Exchange over the network of devices
* In a connected network, multiple devices exchange information and the data must be formatted into a packet before it is sent over the air.
* The types of data exchanged can be some information, alerts, requests and responses.
* It is possible that data might get corrupted or lost before it reaches the destination.

## Challenge-3a
* Understand the given code which is part of the **packertiser.c** and **packetiser.h** file
* **crc16.c** and **checksum.h** are only used for crc calculations and no need to understand the code.

```
    status_t packetiser(packet_t* result_packet, uint8_t* data, uint8_t data_length);

    status_t crc_calculator(uint8_t* data, uint8_t data_length);

    void display_packet(packet_t* input_packet);

    status_t verify_crc(packet_t* input_packet);
```

## Challenge-3b
* Write additional functions to use the code to generate different types of Packets
* Ex: Request packets, Response packets, Alert packets, Information packets
* You can create your own formats within **data** section of the packet_t for different packet types

## Challenge-3c
* Test all the functions written using Unit testing framework
* Use [Unity](http://www.throwtheswitch.org/unity) as a framework for unit testing

### Resources to learn usage of Unity
* [Simple usage](https://github.com/stepin654321/MiniProject_Template/blob/master/HOWTO.md#step3---add-unity-test-framework-to-codeblocks) of Unity functions 
* [Factorial](https://github.com/stepin654321/MiniProject_Template/tree/master/Example_Programs/Factorial) example
* [PhoneBook](https://github.com/stepin654321/MiniProject_Template/tree/master/Example_Programs/PhoneBook) example
 