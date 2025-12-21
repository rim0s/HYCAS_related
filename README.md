# HYCAS_related

HYCAS是一款超市的业务管理系统。其中包括了门店收银终端程序，采购，物流，商品、价格、促销、会员、线上接口等非常繁多的功能模块。
我很多年前在连锁超市工作时候负责信息部门的技术工作。工作过程为了解决技术人员水平参差不齐，各部门使用软件系统各个模块问题，应急问题等，选择使用不需要依赖不需要第三方程序就能运行的批处理程序的方法来解决一些实际问题。
我离职以后已经将之前公司同事，无论是技术人员还是门店人员，能用到的程序、脚本、和资料都放在weiyun.com进行了共享。这么多年为了维持共享可用一直每月续费维持存储空间。现在我把一些程序和脚本放到这里，可能weiyun就不再续费了。


1.前台备分收银流水文件并覆盖空库.bat    # 功能是字面意思，我已经把代码中当时为了给其他技术人员看的联系方式信息去除了。

2.临时解决外卖平台导致实物流水报错问题$  # 功能是字面意思，请忽略错别字。我在上传前去除了保存有密码的crt2.dll文件。主脚本"双击我.bat"是一键执行。程序使用了对称算法对包含语句的主脚本内容，和操作数据库所需的密码进行了加密。双击我.bat会对主要逻辑脚本解密，主要逻辑脚本在适当时候对数据库SQL脚本和连接密码进行解密。执行后对中间文件进行清理。为了能使用对陈算法我找到了一个版本的openssl 的windows包。这也是为什么这个功能的批处理会包含文件夹和这么多文件其实这些头文件和c文件不是必须的，但是这个程序是要给各个技术人员去分别在各自负责的门店去执行的，为了在出现不适配的情况下能有进行编译来补救的机会，我保留了这些文件。我对内容进行加密当时并不是为了保密，而是防止误操作导致篡改了文件以至于操作数据库这样的危险操作产生无法补救的后果。
我的脚本都很槽，因为我其实并不擅长写脚本。只是为了解决问题而去了解和使用的。因为windows的batch和linux的shell脚本都是系统自带直接就能使用，不需要准备环境和找第三方程序，除非有必须使用的第三方程序功能的时候。
└── 进入次文件夹
    ├── 双击我.bat
    ├── Correct.dll
    ├── crt2.dll
    ├── input2.txt
    ├── openssl
    │   ├── bin
    │   │   ├── libeay32.dll
    │   │   ├── openssl.exe
    │   │   └── ssleay32.dll
    │   ├── include
    │   │   └── openssl
    │   │       ├── aes.h
    │   │       ├── applink.c
    │   │       ├── asn1.h
    │   │       ├── asn1_mac.h
    │   │       ├── asn1t.h
    │   │       ├── bio.h
    │   │       ├── blowfish.h
    │   │       ├── bn.h
    │   │       ├── buffer.h
    │   │       ├── camellia.h
    │   │       ├── cast.h
    │   │       ├── cmac.h
    │   │       ├── cms.h
    │   │       ├── comp.h
    │   │       ├── conf_api.h
    │   │       ├── conf.h
    │   │       ├── crypto.h
    │   │       ├── des.h
    │   │       ├── des_old.h
    │   │       ├── dh.h
    │   │       ├── dsa.h
    │   │       ├── dso.h
    │   │       ├── dtls1.h
    │   │       ├── ebcdic.h
    │   │       ├── ecdh.h
    │   │       ├── ecdsa.h
    │   │       ├── ec.h
    │   │       ├── engine.h
    │   │       ├── e_os2.h
    │   │       ├── err.h
    │   │       ├── evp.h
    │   │       ├── hmac.h
    │   │       ├── idea.h
    │   │       ├── krb5_asn.h
    │   │       ├── kssl.h
    │   │       ├── lhash.h
    │   │       ├── md4.h
    │   │       ├── md5.h
    │   │       ├── mdc2.h
    │   │       ├── modes.h
    │   │       ├── objects.h
    │   │       ├── obj_mac.h
    │   │       ├── ocsp.h
    │   │       ├── opensslconf.h
    │   │       ├── opensslv.h
    │   │       ├── ossl_typ.h
    │   │       ├── pem2.h
    │   │       ├── pem.h
    │   │       ├── pkcs12.h
    │   │       ├── pkcs7.h
    │   │       ├── pqueue.h
    │   │       ├── rand.h
    │   │       ├── rc2.h
    │   │       ├── rc4.h
    │   │       ├── ripemd.h
    │   │       ├── rsa.h
    │   │       ├── safestack.h
    │   │       ├── seed.h
    │   │       ├── sha.h
    │   │       ├── srp.h
    │   │       ├── srtp.h
    │   │       ├── ssl23.h
    │   │       ├── ssl2.h
    │   │       ├── ssl3.h
    │   │       ├── ssl.h
    │   │       ├── stack.h
    │   │       ├── symhacks.h
    │   │       ├── tls1.h
    │   │       ├── ts.h
    │   │       ├── txt_db.h
    │   │       ├── ui_compat.h
    │   │       ├── ui.h
    │   │       ├── whrlpool.h
    │   │       ├── x509.h
    │   │       ├── x509v3.h
    │   │       └── x509_vfy.h
    │   ├── lib
    │   │   ├── engines
    │   │   │   ├── 4758cca.dll
    │   │   │   ├── aep.dll
    │   │   │   ├── atalla.dll
    │   │   │   ├── capi.dll
    │   │   │   ├── chil.dll
    │   │   │   ├── cswift.dll
    │   │   │   ├── gmp.dll
    │   │   │   ├── gost.dll
    │   │   │   ├── nuron.dll
    │   │   │   ├── padlock.dll
    │   │   │   ├── sureware.dll
    │   │   │   └── ubsec.dll
    │   │   ├── libeay32.lib
    │   │   └── ssleay32.lib
    │   └── ssl
    │       └── openssl.cnf
    └── output.txt


