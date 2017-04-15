#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Copyright 2017 Daniel Estevez <daniel@destevez.net>
# 
# This is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this software; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
# 


from gnuradio import gr

import struct
import socket
import threading

class linrad_server(gr.basic_block):
    """
    docstring for block linrad_server
    """
    def __init__(self, listen_ip, samp_rate, ad_channels, rf_channels, bufsize, iq_data, dword_input):
        gr.basic_block.__init__(self,
            name="linrad_server",
            in_sig=[],
            out_sig=[])

        self.listen_ip = listen_ip
        self.samp_rate = samp_rate
        self.ad_channels = ad_channels
        self.rf_channels = rf_channels
        self.bufsize = bufsize
        # input mode = 1 -> DWORD_INPUT
        # input mode = 4 -> IQ_DATA
        self.input_mode = dword_input | iq_data << 2

        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.bind((listen_ip, 49812))
        self.socket.listen(1)
        
        t = threading.Thread(target=self.server)
        t.start()

    def server(self):
        while True:
            conn, addr = self.socket.accept()
            t = threading.Thread(target=self.handle_client, args=(conn, ))
            t.start()

    def handle_client(self, conn):
        try:
            while True:
                data = conn.recv(1024)
                if not data: break
                if len(data) == 0: continue
                if data[0] == '\xb8':
                    response = struct.pack('<8i', self.samp_rate, self.ad_channels,\
                                           self.rf_channels, self.input_mode, self.bufsize, 0, 0, 0)
                    conn.send(response)
                elif data[0] == '\xb5' or data[0] == '\xb6':
                    conn.send('\x00')
        finally:
            conn.close()

