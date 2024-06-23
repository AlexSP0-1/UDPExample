# UDPExample

## TOC

* [Release Notes](#Notes)
* [Usage](#Usage)
* [Description](#Description)

## Notes

IMPORTANT. Please, see description.md file.

## Usage

### udp_ex_client [options]

Options:

  ```
  -h, --help                Displays help on commandline options.
  --help-all                Displays help including Qt specific options.
  -v, --version             Displays version information.
  -p, --port <port>         Specifies the port for the request. If not pecified, 11123 will be used.
  -a, --address <address>  Specifies the ip4 address for the request. If not specified, localhost will be used.
  -r, --resource <address>  Specifies the resource name for the request.
  ```

### Usage: udp_ex_server [options]

Options:
```
  -h, --help         Displays help on commandline options.
  --help-all         Displays help including Qt specific options.
  -v, --version      Displays version information.
  -p, --port <port>  Specify port to listen. If not specified will be listen on default port 11123
  -f, --file <file>  Gets resourcves from file.
```

## Description

Test Assignment

Write two applications:
1. "A "server" listening on a given UDP port.
In an incoming packet, the server accepts the name of a resource requested from it.
In the outgoing packet, the server frames the contents of the resource:
-BEGIN-.
content
-END-.

The correspondence between the resource name and its contents can be specified in a text file, for example:
resource1 Hello
 resource2 World
 resource3 Thank you

From the given example, when requesting resource1 resource, the server should return:
-BEGIN-.
Hello
 -END-

Assumption:
- the resource name is up to 64 bytes long.
- the resource content and framing does not exceed 1024 bytes.

There are no restrictions on the implementation of the incoming packet format.
There are no restrictions on the method of specifying correspondences between the resource name and its contents (single file or file system hierarchy, etc.).

When errors occur, the outgoing packet must contain:
-ERROR-
code or error text
-END-

A plus would be the realization of the possibility of parallel processing of "simultaneously" received requests.

2. A client that accepts via command line parameters the name of the requested resource and displays (stdout/stderr) the server response.
A plus would be the realization of the possibility of parallel processing of "simultaneously" received requests.

2. A client that accepts via command line parameters the name of the requested resource and displays (stdout/stderr) the server response.
