#!/bin/bash

bashtest()
{
	echo $*
	echo $* | bash; echo $?
}

line()
{
	echo "---------------------------"
}

bashtest $*
