# MattDaemon
🌐 💾 A pointless website backup daemon written in c

## Configuration
Configuration of the daemon can be done by changing the macros found within the config header.


## Build
* To build simply run the following from the ./code/src subdirectory
```BASH
    make clean
    make
```

## Usage
The following are the available program parameters:
* start: To start the daemon
* backup: To make a backup of the LIVE directory
* transfer: To transfer files from the SOURCE to LIVE directory
* btransfer: To execute a backup followed by a transfer