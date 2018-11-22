# Jbcoind Docker Image

Jbcoind has a continuous deployment pipeline that turns every git commit into a
docker image for quick testing and deployment.

To run the tip of the latest release via docker:

```$ docker run -P -v /srv/jbcoind/ jbcoin/jbcoind:latest```

To run the tip of active development:

```$ docker run -P -v /srv/jbcoind/ jbcoin/jbcoind:develop```

Where ```/srv/jbcoind``` points to a directory containing a jbcoind.cfg and
database files. By default, port 5005/tcp maps to the RPC port and 51235/udp to
the peer port.
