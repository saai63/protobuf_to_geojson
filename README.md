## protobuf_to_geojson

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

![Build](https://github.com/saai63/protobuf_to_geojson/workflows/Build_Project/badge.svg)

### Motivation
Any application that needs to work with geographical data would need some kind of visualization tools.
[GEOJSON](https://en.wikipedia.org/wiki/GeoJSON) is one such convenient format to visualize GIS data. However, since GEOJSON is a textual format, the space consumption would be pretty high.
In order to get around this problem, we can use [ProtoBuf](https://developers.google.com/protocol-buffers) which is a more optimized format for data exchange.

We could first write the data in protobuf format to optimize the space used and later convert protobuf to geojson when needed for visualization.

### How to run
* GitHub actions execute the tests.
* Creation of protobuf file seems to be OK.
* When we try to create JSON from protobuf, an exception is being thrown.
