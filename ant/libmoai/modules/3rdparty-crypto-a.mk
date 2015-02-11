#================================================================#
# Copyright (c) 2010-2011 Zipline Games, Inc.
# All Rights Reserved.
# http://getmoai.com
#================================================================#

	include $(CLEAR_VARS)

	LOCAL_MODULE 		:= crypto-a
	LOCAL_ARM_MODE 		:= $(MY_ARM_MODE)
	LOCAL_CFLAGS 		:= $(MY_CFLAGS) -w -DL_ENDIAN -DOPENSSL_NO_GMP -DOPENSSL_NO_JPAKE -DOPENSSL_NO_MD2 -DOPENSSL_NO_RC5 -DOPENSSL_NO_RFC3779 -DOPENSSL_NO_STORE
	LOCAL_CFLAGS		+= -include $(MOAI_SDK_HOME)/src/zl-vfs/zl_replace.h
	LOCAL_CFLAGS		+= -fvisibility=hidden

	LOCAL_C_INCLUDES 	+= $(MY_HEADER_SEARCH_PATHS)
	LOCAL_C_INCLUDES 	+= '$(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1'

	#Name="asn1"
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/a_bitstr.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/a_bool.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/a_bytes.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/a_d2i_fp.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/a_digest.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/a_dup.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/a_enum.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/a_gentm.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/a_i2d_fp.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/a_int.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/a_mbstr.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/a_object.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/a_octet.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/a_print.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/a_set.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/a_sign.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/a_strex.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/a_strnid.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/a_time.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/a_type.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/a_utctm.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/a_utf8.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/a_verify.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/ameth_lib.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/asn1_err.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/asn1_gen.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/asn1_lib.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/asn1_par.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/asn_mime.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/asn_moid.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/asn_pack.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/bio_asn1.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/bio_ndef.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/d2i_pr.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/d2i_pu.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/evp_asn1.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/f_enum.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/f_int.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/f_string.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/i2d_pr.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/i2d_pu.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/n_pkey.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/nsseq.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/p5_pbe.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/p5_pbev2.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/p8_pkey.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/t_bitst.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/t_crl.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/t_pkey.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/t_req.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/t_spki.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/t_x509.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/t_x509a.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/tasn_dec.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/tasn_enc.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/tasn_fre.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/tasn_new.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/tasn_prn.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/tasn_typ.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/tasn_utl.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/x_algor.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/x_attrib.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/x_bignum.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/x_crl.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/x_exten.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/x_info.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/x_long.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/x_name.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/x_nx509.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/x_pkey.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/x_pubkey.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/x_req.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/x_sig.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/x_spki.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/x_val.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/x_x509.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/asn1/x_x509a.c

	#Name="conf"
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/conf/conf_api.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/conf/conf_def.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/conf/conf_err.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/conf/conf_lib.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/conf/conf_mall.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/conf/conf_mod.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/conf/conf_sap.c

	#Name="engine"
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/engine/eng_all.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/engine/eng_cnf.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/engine/eng_cryptodev.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/engine/eng_ctrl.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/engine/eng_dyn.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/engine/eng_err.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/engine/eng_fat.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/engine/eng_init.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/engine/eng_lib.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/engine/eng_list.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/engine/eng_openssl.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/engine/eng_pkey.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/engine/eng_table.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/engine/tb_asnmth.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/engine/tb_cipher.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/engine/tb_dh.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/engine/tb_digest.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/engine/tb_dsa.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/engine/tb_ecdh.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/engine/tb_ecdsa.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/engine/tb_pkmeth.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/engine/tb_rand.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/engine/tb_rsa.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/engine/tb_store.c

	#Name="evp"
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/bio_b64.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/bio_enc.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/bio_md.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/bio_ok.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/c_all.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/c_allc.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/c_alld.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/digest.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/e_aes.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/e_bf.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/e_camellia.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/e_cast.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/e_des.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/e_des3.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/e_idea.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/e_null.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/e_old.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/e_rc2.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/e_rc4.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/e_rc5.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/e_seed.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/e_xcbc_d.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/encode.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/evp_acnf.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/evp_enc.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/evp_err.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/evp_key.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/evp_lib.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/evp_pbe.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/evp_pkey.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/m_dss.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/m_dss1.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/m_ecdsa.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/m_md2.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/m_md4.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/m_md5.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/m_mdc2.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/m_null.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/m_ripemd.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/m_sha.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/m_sha1.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/m_sigver.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/m_wp.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/names.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/p5_crpt.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/p5_crpt2.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/p_dec.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/p_enc.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/p_lib.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/p_open.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/p_seal.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/p_sign.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/p_verify.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/pmeth_fn.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/pmeth_gn.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/evp/pmeth_lib.c

	#Name="lhash"
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/lhash/lh_stats.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/lhash/lhash.c

	#Name="ocsp"
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/ocsp/ocsp_asn.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/ocsp/ocsp_cl.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/ocsp/ocsp_err.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/ocsp/ocsp_ext.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/ocsp/ocsp_ht.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/ocsp/ocsp_lib.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/ocsp/ocsp_prn.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/ocsp/ocsp_srv.c
	LOCAL_SRC_FILES += $(MOAI_SDK_HOME)/3rdparty/openssl-1.0.0m/crypto/ocsp/ocsp_vfy.c

	include $(BUILD_STATIC_LIBRARY)
