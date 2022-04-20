@echo off


rem 디렉토리 생성
IF not exist opensource (
	md opensource
)
cd opensource

rem ----------------------------------------------------------------------
rem 첫번째 파라매터 확인 후 토큰 받기
SET _argc=0
FOR %%i in (%*) do set /A _argc+=1
rem echo argc is %_argc%!
IF not %_argc%==1 (
	echo Usage : %0 [Github token]
	goto ExitBatch
)


rem ----------------------------------------------------------------------
rem 소스 다운받기 (owpml)

echo -------
echo OSS download : owpml-model
IF not exist hwpx-owpml-model (
	git clone https://%1@github.com/hancom-io/hwpx-owpml-model.git
)
cd hwpx-owpml-model
git pull
cd ..


rem ----------------------------------------------------------------------
rem 소스 다운받기 (rapidjson)

echo -------
echo OSS download : rapidjson
IF not exist rapidjson (
	git clone https://%1@github.com/Tencent/rapidjson.git
	git pull
)
SET _rapidjson_RESETID="8261c1ddf43f10de00fd8c9a67811d1486b2c784"
cd rapidjson
git reset --hard %_rapidjson_RESETID%
cd ..

rem ----------------------------------------------------------------------
rem 소스 다운받기 (jsoncpp)

echo -------
echo OSS download : jsoncpp
IF not exist jsoncpp (
	git clone https://%1@github.com/open-source-parsers/jsoncpp.git
	git pull
)
SET _jsoncpp_RESETID="8190e061bc2d95da37479a638aa2c9e483e58ec6"
cd rapidjson
git reset --hard %_jsoncpp_RESETID%
cd ..


rem ----------------------------------------------------------------------
rem 원 디렉토리 복귀
:ExitBatch
cd ..
exit /b