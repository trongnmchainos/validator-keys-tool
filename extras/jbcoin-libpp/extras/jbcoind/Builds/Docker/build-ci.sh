set -e

mkdir -p build/docker/
cp doc/jbcoind-example.cfg build/clang.debug/jbcoind build/docker/
cp Builds/Docker/Dockerfile-testnet build/docker/Dockerfile
mv build/docker/jbcoind-example.cfg build/docker/jbcoind.cfg
strip build/docker/jbcoind
docker build -t jbcoin/jbcoind:$CIRCLE_SHA1 build/docker/
docker tag jbcoin/jbcoind:$CIRCLE_SHA1 jbcoin/jbcoind:latest

if [ -z "$CIRCLE_PR_NUMBER" ]; then
  docker tag jbcoin/jbcoind:$CIRCLE_SHA1 jbcoin/jbcoind:$CIRCLE_BRANCH
fi
