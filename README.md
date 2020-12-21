# CollabServer Framework

## Overview

Framework for Real-time collaboration on extensive Data Types using Strong Eventual Consistency (SEC).
This is an archive of the CollabServer Framework.
The official github organization is located at this address: <https://github.com/collabserver>

## Getting Started

Follow the build instruction in **collabserver-grapheditor**.

## Projects architecture

- **collabserver-grapheditor**
Example of a command line graph editor for realtime collaboration using the CollabServer Framework
- **collabserver-datatypes**
Set of data types (CRDTs) to build a collaborative data usable with the CollabServer Framework
- **collabserver-client**
Client interface to connect a user collaborative data (built with collabdata-datatype) with a the CollabServer server
- **collabserver-server**
Server to create realtime collaborative rooms
- **collabserver-network**
Network code used by the client and server (e.g., messaging protocol and socket)
