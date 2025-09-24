#!/bin/bash

if [ -z "$SUDO_USER" ]; then
    echo "This script is NOT running with sudo permissions."
    exit 1
fi

INSTALLDIR="/opt/orchestrator"

ORCHESTRATORCLI="/home/fernando/Repos/DeviceIQ-Orchestrator-CLI/build/bin"
ORCHESTRATORSVR="/home/fernando/Repos/DeviceIQ-Orchestrator-Server/build/bin"

ORCHESTRATORCLI_BIN="Orchestrator-CLI"
ORCHESTRATORSVR_BIN="Orchestrator-Server"

clear
echo "Orchestrator Server Deploy"
systemctl stop orchestrator
echo ""
cp $ORCHESTRATORCLI/$ORCHESTRATORCLI_BIN $ORCHESTRATORSVR -v
cp $ORCHESTRATORSVR/$ORCHESTRATORSVR_BIN $INSTALLDIR -v
cp $ORCHESTRATORSVR/$ORCHESTRATORCLI_BIN $INSTALLDIR -v
echo ""
systemctl start orchestrator
echo "Done."
