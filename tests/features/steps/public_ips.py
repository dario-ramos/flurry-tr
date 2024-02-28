import random

# 8.* : Google DNS, 1.* : Cloudflare, 9.*: Quad9 DNS, 4.*: Verizon
public_ips = ['8.8.8.8', '8.8.4.4', '4.2.2.2', '4.2.2.3', '1.1.1.1', '1.0.0.1', '9.9.9.9']

# Some IP addresses cause issues with some scamper commands, so we omit them and use
# this restricted list for those cases.
public_ips_restricted = ['4.2.2.2', '4.2.2.3', '1.1.1.1', '1.0.0.1', '9.9.9.9']

def get_public_ip():
	return random.choice(public_ips)

def get_public_ip_restricted():
	return random.choice(public_ips_restricted)
