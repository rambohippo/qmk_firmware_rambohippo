If receiving a verification error when compiling, it may have to do with
the Modem Manager service. To confirm that this is indeed the issue, 
run the following command:

    systemctl status ModemManager.service

If an error appears about being unable to work with one of the /dev/
devices, run the next command to fix:

    sudo systemctl stop ModemManager.service
