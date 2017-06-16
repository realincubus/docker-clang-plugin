#!/bin/bash
cd /root/optci/unit_tests && ctest --no-compress-output -T Test .
rm -rf /host/*
cp -r /root/optci/unit_tests/Testing /host/optci_results
chmod 777 -R /host

