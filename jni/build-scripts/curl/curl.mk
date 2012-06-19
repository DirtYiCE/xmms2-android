include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
	$(CURL_SOURCE)/file.c \
	$(CURL_SOURCE)/timeval.c \
	$(CURL_SOURCE)/base64.c \
	$(CURL_SOURCE)/hostip.c \
	$(CURL_SOURCE)/progress.c \
	$(CURL_SOURCE)/formdata.c\
	$(CURL_SOURCE)/cookie.c \
	$(CURL_SOURCE)/http.c \
	$(CURL_SOURCE)/sendf.c \
	$(CURL_SOURCE)/ftp.c \
	$(CURL_SOURCE)/url.c \
	$(CURL_SOURCE)/dict.c \
	$(CURL_SOURCE)/if2ip.c \
	$(CURL_SOURCE)/speedcheck.c\
	$(CURL_SOURCE)/ldap.c \
	$(CURL_SOURCE)/ssluse.c \
	$(CURL_SOURCE)/version.c \
	$(CURL_SOURCE)/getenv.c \
	$(CURL_SOURCE)/escape.c \
	$(CURL_SOURCE)/mprintf.c \
	$(CURL_SOURCE)/telnet.c\
	$(CURL_SOURCE)/netrc.c \
	$(CURL_SOURCE)/getinfo.c \
	$(CURL_SOURCE)/transfer.c \
	$(CURL_SOURCE)/strequal.c \
	$(CURL_SOURCE)/easy.c \
	$(CURL_SOURCE)/security.c \
	$(CURL_SOURCE)/krb4.c \
	$(CURL_SOURCE)/curl_fnmatch.c \
	$(CURL_SOURCE)/fileinfo.c \
	$(CURL_SOURCE)/ftplistparser.c \
	$(CURL_SOURCE)/wildcard.c \
	$(CURL_SOURCE)/krb5.c \
	$(CURL_SOURCE)/memdebug.c \
	$(CURL_SOURCE)/http_chunks.c \
	$(CURL_SOURCE)/strtok.c \
	$(CURL_SOURCE)/connect.c \
	$(CURL_SOURCE)/llist.c \
	$(CURL_SOURCE)/hash.c \
	$(CURL_SOURCE)/multi.c \
	$(CURL_SOURCE)/content_encoding.c \
	$(CURL_SOURCE)/share.c \
	$(CURL_SOURCE)/http_digest.c \
	$(CURL_SOURCE)/md4.c \
	$(CURL_SOURCE)/md5.c \
	$(CURL_SOURCE)/curl_rand.c \
	$(CURL_SOURCE)/http_negotiate.c \
	$(CURL_SOURCE)/inet_pton.c \
	$(CURL_SOURCE)/strtoofft.c \
	$(CURL_SOURCE)/strerror.c \
	$(CURL_SOURCE)/amigaos.c \
	$(CURL_SOURCE)/hostasyn.c \
	$(CURL_SOURCE)/hostip4.c \
	$(CURL_SOURCE)/hostip6.c \
	$(CURL_SOURCE)/hostsyn.c \
	$(CURL_SOURCE)/inet_ntop.c \
	$(CURL_SOURCE)/parsedate.c \
	$(CURL_SOURCE)/select.c \
	$(CURL_SOURCE)/gtls.c \
	$(CURL_SOURCE)/sslgen.c \
	$(CURL_SOURCE)/tftp.c \
	$(CURL_SOURCE)/splay.c \
	$(CURL_SOURCE)/strdup.c \
	$(CURL_SOURCE)/socks.c \
	$(CURL_SOURCE)/ssh.c \
	$(CURL_SOURCE)/nss.c \
	$(CURL_SOURCE)/qssl.c \
	$(CURL_SOURCE)/rawstr.c \
	$(CURL_SOURCE)/curl_addrinfo.c \
	$(CURL_SOURCE)/socks_gssapi.c \
	$(CURL_SOURCE)/socks_sspi.c \
	$(CURL_SOURCE)/curl_sspi.c \
	$(CURL_SOURCE)/slist.c \
	$(CURL_SOURCE)/nonblock.c \
	$(CURL_SOURCE)/curl_memrchr.c \
	$(CURL_SOURCE)/imap.c \
	$(CURL_SOURCE)/pop3.c \
	$(CURL_SOURCE)/smtp.c \
	$(CURL_SOURCE)/pingpong.c \
	$(CURL_SOURCE)/rtsp.c \
	$(CURL_SOURCE)/curl_threads.c \
	$(CURL_SOURCE)/warnless.c \
	$(CURL_SOURCE)/hmac.c \
	$(CURL_SOURCE)/polarssl.c \
	$(CURL_SOURCE)/curl_rtmp.c \
	$(CURL_SOURCE)/openldap.c \
	$(CURL_SOURCE)/curl_gethostname.c \
	$(CURL_SOURCE)/gopher.c \
	$(CURL_SOURCE)/axtls.c \
	$(CURL_SOURCE)/idn_win32.c \
	$(CURL_SOURCE)/http_negotiate_sspi.c \
	$(CURL_SOURCE)/cyassl.c \
	$(CURL_SOURCE)/http_proxy.c \
	$(CURL_SOURCE)/non-ascii.c \
	$(CURL_SOURCE)/asyn-ares.c \
	$(CURL_SOURCE)/asyn-thread.c \
	$(CURL_SOURCE)/curl_gssapi.c \
	$(CURL_SOURCE)/curl_ntlm.c \
	$(CURL_SOURCE)/curl_ntlm_wb.c \
	$(CURL_SOURCE)/curl_ntlm_core.c \
	$(CURL_SOURCE)/curl_ntlm_msgs.c \
	$(CURL_SOURCE)/curl_sasl.c \
	$(CURL_SOURCE)/curl_schannel.c \
	$(CURL_SOURCE)/curl_multibyte.c

LOCAL_C_INCLUDES := $(CURL_INCLUDE) $(CURL_CONFIG)/curl
LOCAL_CFLAGS := -Wpointer-arith -Wwrite-strings -Wunused -Winline -Wnested-externs -Wmissing-declarations -Wmissing-prototypes -Wno-long-long -Wfloat-equal -Wno-multichar -Wsign-compare -Wno-format-nonliteral -Wendif-labels -Wstrict-prototypes -Wdeclaration-after-statement -Wno-system-headers -DHAVE_CONFIG_H

LOCAL_LDLIBS := -lz
LOCAL_MODULE := curllib

include $(BUILD_STATIC_LIBRARY)
