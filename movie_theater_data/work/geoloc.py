#!/usr/bin/python
# -*- coding: UTF8 -*-

from googlemaps import GoogleMaps

def get_loc(address):

	api_key = "ABQIAAAA_Nl9CTT83Tx0_6m45f7SQxRfRo7TXTpgZcKZw6sB7U7ZlfQK2BQV36qlGpf3-HF0Ntlqdf8T-Gaqxg"

	gmaps = GoogleMaps(api_key)

	lat, lng = gmaps.address_to_latlng(address)

	print lat, lng

	return lat, lng

