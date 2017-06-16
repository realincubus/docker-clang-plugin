#!/bin/bash
cd /root/optci/unit_tests && ctest --no-compress-output -T Test .
cp -r /root/optci/unit_tests/Testing /host/optci_results
chmod 777 -R /host

