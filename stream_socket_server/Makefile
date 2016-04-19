#unix_domain_sv : us_xfr_sv.c error_functions.c
#	cc -o unix_domain_sv us_xfr_sv.c error_functions.c

stream_socket : is_seqnum_sv.c is_seqnum_cl.c error_functions.c get_num.c
	cc -o stream_socket_sv is_seqnum_sv.c error_functions.c get_num.c
	cc -o stream_socket_cl is_seqnum_cl.c error_functions.c get_num.c
