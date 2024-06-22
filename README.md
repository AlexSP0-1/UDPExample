# UDPExample
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

Translated with DeepL.com (free version)