#!/bin/sh

socat TCP-LISTEN:5001,reuseaddr,fork,su=chall EXEC:"./chall",stderr