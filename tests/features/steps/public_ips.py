import random

# 8.* : Google DNS, 1.* : Cloudflare, 9.*: Quad9 DNS
public_ips = ['8.8.8.8', '8.8.4.4', '4.2.2.2', '1.1.1.1', '1.0.0.1', '9.9.9.9']

def get_public_ip():
	return random.choice(public_ips)
