#!/usr/bin/python -u
# encoding: utf-8

import os
program_name = 'findme'

if __name__ == '__main__':
    args = [program_name] + raw_input().split(' ')
    env = os.environ
    os.execlp(program_name, *args)





