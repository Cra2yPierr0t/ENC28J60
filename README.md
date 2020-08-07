# ENC28J60

FPGAでENC28J60を動かしたい で書いたコード達

* assembler.c       : ENC28J60用アセンブラ
* enc_driver_top.sv : ENC28J60用ドライバ
* enc_driver.sv     : SPIドライバ(書き込みのみ)
* prog.S            : フレーム送信用命令
* ROM.v             : 命令メモリ
* instr.mif         : ROM.v用初期化ファイル
* bin               : フレーム送信用命令バイナリ
