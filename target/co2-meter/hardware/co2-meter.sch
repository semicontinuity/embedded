<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="7.5.0">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="yes" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="50" name="dxf" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
<layer number="100" name="NonViaHole" color="14" fill="1" visible="no" active="yes"/>
<layer number="101" name="PlacementGuide" color="7" fill="1" visible="no" active="yes"/>
<layer number="200" name="200bmp" color="1" fill="10" visible="no" active="no"/>
<layer number="201" name="201bmp" color="2" fill="10" visible="no" active="yes"/>
<layer number="250" name="Descript" color="7" fill="1" visible="no" active="yes"/>
<layer number="251" name="SMDround" color="7" fill="1" visible="no" active="yes"/>
<layer number="254" name="OrgLBR" color="7" fill="1" visible="no" active="yes"/>
</layers>
<schematic>
<libraries>
<library name="con-lstb">
<description>&lt;b&gt;Pin Headers&lt;/b&gt;&lt;p&gt;
Naming:&lt;p&gt;
MA = male&lt;p&gt;
# contacts - # rows&lt;p&gt;
W = angled&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="MA08-1">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<wire x1="-9.525" y1="1.27" x2="-8.255" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-8.255" y1="1.27" x2="-7.62" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-7.62" y1="-0.635" x2="-8.255" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-7.62" y1="0.635" x2="-6.985" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-6.985" y1="1.27" x2="-5.715" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-5.715" y1="1.27" x2="-5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="-0.635" x2="-5.715" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-5.715" y1="-1.27" x2="-6.985" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-6.985" y1="-1.27" x2="-7.62" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="0.635" x2="-10.16" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-9.525" y1="1.27" x2="-10.16" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="-0.635" x2="-9.525" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-8.255" y1="-1.27" x2="-9.525" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="0.635" x2="-4.445" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-4.445" y1="1.27" x2="-3.175" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="1.27" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-0.635" x2="-3.175" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="-1.27" x2="-4.445" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-4.445" y1="-1.27" x2="-5.08" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="1.27" x2="-0.635" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="1.27" x2="0" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="-0.635" x2="-0.635" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="1.27" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-0.635" x2="-1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="-1.27" x2="-1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="0.635" y1="1.27" x2="1.905" y2="1.27" width="0.1524" layer="21"/>
<wire x1="1.905" y1="1.27" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-0.635" x2="1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="2.54" y1="0.635" x2="3.175" y2="1.27" width="0.1524" layer="21"/>
<wire x1="3.175" y1="1.27" x2="4.445" y2="1.27" width="0.1524" layer="21"/>
<wire x1="4.445" y1="1.27" x2="5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="5.08" y1="-0.635" x2="4.445" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="4.445" y1="-1.27" x2="3.175" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="3.175" y1="-1.27" x2="2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="0.635" y1="1.27" x2="0" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="-0.635" x2="0.635" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-1.27" x2="0.635" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="5.08" y1="0.635" x2="5.715" y2="1.27" width="0.1524" layer="21"/>
<wire x1="5.715" y1="1.27" x2="6.985" y2="1.27" width="0.1524" layer="21"/>
<wire x1="6.985" y1="1.27" x2="7.62" y2="0.635" width="0.1524" layer="21"/>
<wire x1="7.62" y1="-0.635" x2="6.985" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="6.985" y1="-1.27" x2="5.715" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="5.715" y1="-1.27" x2="5.08" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="8.255" y1="1.27" x2="9.525" y2="1.27" width="0.1524" layer="21"/>
<wire x1="9.525" y1="1.27" x2="10.16" y2="0.635" width="0.1524" layer="21"/>
<wire x1="10.16" y1="0.635" x2="10.16" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="10.16" y1="-0.635" x2="9.525" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="8.255" y1="1.27" x2="7.62" y2="0.635" width="0.1524" layer="21"/>
<wire x1="7.62" y1="-0.635" x2="8.255" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="9.525" y1="-1.27" x2="8.255" y2="-1.27" width="0.1524" layer="21"/>
<pad name="1" x="-8.89" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="2" x="-6.35" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="3" x="-3.81" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="4" x="-1.27" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="5" x="1.27" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="6" x="3.81" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="7" x="6.35" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="8" x="8.89" y="0" drill="1.016" shape="long" rot="R90"/>
<text x="-10.16" y="1.651" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-9.398" y="-2.921" size="1.27" layer="21" ratio="10">1</text>
<text x="8.255" y="1.651" size="1.27" layer="21" ratio="10">8</text>
<text x="-1.27" y="-2.921" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-6.604" y1="-0.254" x2="-6.096" y2="0.254" layer="51"/>
<rectangle x1="-9.144" y1="-0.254" x2="-8.636" y2="0.254" layer="51"/>
<rectangle x1="-4.064" y1="-0.254" x2="-3.556" y2="0.254" layer="51"/>
<rectangle x1="-1.524" y1="-0.254" x2="-1.016" y2="0.254" layer="51"/>
<rectangle x1="3.556" y1="-0.254" x2="4.064" y2="0.254" layer="51"/>
<rectangle x1="1.016" y1="-0.254" x2="1.524" y2="0.254" layer="51"/>
<rectangle x1="6.096" y1="-0.254" x2="6.604" y2="0.254" layer="51"/>
<rectangle x1="8.636" y1="-0.254" x2="9.144" y2="0.254" layer="51"/>
</package>
</packages>
<symbols>
<symbol name="MA08-1">
<wire x1="3.81" y1="-10.16" x2="-1.27" y2="-10.16" width="0.4064" layer="94"/>
<wire x1="1.27" y1="-2.54" x2="2.54" y2="-2.54" width="0.6096" layer="94"/>
<wire x1="1.27" y1="-5.08" x2="2.54" y2="-5.08" width="0.6096" layer="94"/>
<wire x1="1.27" y1="-7.62" x2="2.54" y2="-7.62" width="0.6096" layer="94"/>
<wire x1="1.27" y1="2.54" x2="2.54" y2="2.54" width="0.6096" layer="94"/>
<wire x1="1.27" y1="0" x2="2.54" y2="0" width="0.6096" layer="94"/>
<wire x1="1.27" y1="10.16" x2="2.54" y2="10.16" width="0.6096" layer="94"/>
<wire x1="1.27" y1="7.62" x2="2.54" y2="7.62" width="0.6096" layer="94"/>
<wire x1="1.27" y1="5.08" x2="2.54" y2="5.08" width="0.6096" layer="94"/>
<wire x1="-1.27" y1="12.7" x2="-1.27" y2="-10.16" width="0.4064" layer="94"/>
<wire x1="3.81" y1="-10.16" x2="3.81" y2="12.7" width="0.4064" layer="94"/>
<wire x1="-1.27" y1="12.7" x2="3.81" y2="12.7" width="0.4064" layer="94"/>
<text x="-1.27" y="-12.7" size="1.778" layer="96">&gt;VALUE</text>
<text x="-1.27" y="13.462" size="1.778" layer="95">&gt;NAME</text>
<pin name="1" x="7.62" y="-7.62" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="2" x="7.62" y="-5.08" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="3" x="7.62" y="-2.54" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="4" x="7.62" y="0" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="5" x="7.62" y="2.54" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="6" x="7.62" y="5.08" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="7" x="7.62" y="7.62" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="8" x="7.62" y="10.16" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="MA08-1" prefix="SV" uservalue="yes">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<gates>
<gate name="1" symbol="MA08-1" x="0" y="0"/>
</gates>
<devices>
<device name="" package="MA08-1">
<connects>
<connect gate="1" pin="1" pad="1"/>
<connect gate="1" pin="2" pad="2"/>
<connect gate="1" pin="3" pad="3"/>
<connect gate="1" pin="4" pad="4"/>
<connect gate="1" pin="5" pad="5"/>
<connect gate="1" pin="6" pad="6"/>
<connect gate="1" pin="7" pad="7"/>
<connect gate="1" pin="8" pad="8"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="esp12">
<packages>
<package name="ESP8266-ESP12">
<wire x1="0" y1="0" x2="16.2" y2="0" width="0.127" layer="21"/>
<wire x1="16.2" y1="0" x2="16.2" y2="24.1" width="0.127" layer="21"/>
<wire x1="16.2" y1="24.1" x2="0" y2="24.1" width="0.127" layer="21"/>
<wire x1="0" y1="24.1" x2="0" y2="0" width="0.127" layer="21"/>
<smd name="16" x="0" y="2" dx="2" dy="1.2" layer="1"/>
<smd name="15" x="0" y="4" dx="2" dy="1.2" layer="1"/>
<smd name="14" x="0" y="6" dx="2" dy="1.2" layer="1"/>
<smd name="13" x="0" y="8" dx="2" dy="1.2" layer="1"/>
<smd name="12" x="0" y="10" dx="2" dy="1.2" layer="1"/>
<smd name="11" x="0" y="12" dx="2" dy="1.2" layer="1"/>
<smd name="10" x="0" y="14" dx="2" dy="1.2" layer="1"/>
<smd name="9" x="0" y="16" dx="2" dy="1.2" layer="1"/>
<smd name="1" x="16.2" y="2" dx="2" dy="1.2" layer="1"/>
<smd name="2" x="16.2" y="4" dx="2" dy="1.2" layer="1"/>
<smd name="3" x="16.2" y="6" dx="2" dy="1.2" layer="1"/>
<smd name="4" x="16.2" y="8" dx="2" dy="1.2" layer="1"/>
<smd name="5" x="16.2" y="10" dx="2" dy="1.2" layer="1"/>
<smd name="6" x="16.2" y="12" dx="2" dy="1.2" layer="1"/>
<smd name="7" x="16.2" y="14" dx="2" dy="1.2" layer="1"/>
<smd name="8" x="16.2" y="16" dx="2" dy="1.2" layer="1"/>
<text x="5" y="2" size="1.27" layer="21" rot="R90">&gt;NAME</text>
<text x="5" y="20" size="1.27" layer="21">ESP-12</text>
</package>
</packages>
<symbols>
<symbol name="ESP12">
<pin name="GND" x="7.62" y="-10.16" length="middle" rot="R180"/>
<pin name="GPIO15" x="7.62" y="-7.62" length="middle" rot="R180"/>
<pin name="GPIO2" x="7.62" y="-5.08" length="middle" rot="R180"/>
<pin name="GPIO0" x="7.62" y="-2.54" length="middle" rot="R180"/>
<pin name="GPIO5" x="7.62" y="0" length="middle" rot="R180"/>
<pin name="GPIO4" x="7.62" y="2.54" length="middle" rot="R180"/>
<pin name="RXD" x="7.62" y="5.08" length="middle" rot="R180"/>
<pin name="TXD" x="7.62" y="7.62" length="middle" rot="R180"/>
<pin name="REST" x="-22.86" y="7.62" length="middle"/>
<pin name="ADC" x="-22.86" y="5.08" length="middle"/>
<pin name="CH_PD" x="-22.86" y="2.54" length="middle"/>
<pin name="GPIO16" x="-22.86" y="0" length="middle"/>
<pin name="GPIO14" x="-22.86" y="-2.54" length="middle"/>
<pin name="GPIO12" x="-22.86" y="-5.08" length="middle"/>
<pin name="GPIO13" x="-22.86" y="-7.62" length="middle"/>
<pin name="VCC" x="-22.86" y="-10.16" length="middle"/>
<wire x1="-17.78" y1="-12.7" x2="2.54" y2="-12.7" width="0.254" layer="94"/>
<wire x1="2.54" y1="-12.7" x2="2.54" y2="10.16" width="0.254" layer="94"/>
<wire x1="2.54" y1="10.16" x2="-17.78" y2="10.16" width="0.254" layer="94"/>
<wire x1="-17.78" y1="10.16" x2="-17.78" y2="-12.7" width="0.254" layer="94"/>
<text x="-17.78" y="-17.78" size="1.27" layer="94">ESP8266_ESP-12</text>
<text x="-17.78" y="-15.24" size="1.27" layer="94">&gt;NAME</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="ESP8266_ESP-12">
<gates>
<gate name="G$1" symbol="ESP12" x="5.08" y="0"/>
</gates>
<devices>
<device name="" package="ESP8266-ESP12">
<connects>
<connect gate="G$1" pin="ADC" pad="10"/>
<connect gate="G$1" pin="CH_PD" pad="11"/>
<connect gate="G$1" pin="GND" pad="1"/>
<connect gate="G$1" pin="GPIO0" pad="4"/>
<connect gate="G$1" pin="GPIO12" pad="14"/>
<connect gate="G$1" pin="GPIO13" pad="15"/>
<connect gate="G$1" pin="GPIO14" pad="13"/>
<connect gate="G$1" pin="GPIO15" pad="2"/>
<connect gate="G$1" pin="GPIO16" pad="12"/>
<connect gate="G$1" pin="GPIO2" pad="3"/>
<connect gate="G$1" pin="GPIO4" pad="6"/>
<connect gate="G$1" pin="GPIO5" pad="5"/>
<connect gate="G$1" pin="REST" pad="9"/>
<connect gate="G$1" pin="RXD" pad="7"/>
<connect gate="G$1" pin="TXD" pad="8"/>
<connect gate="G$1" pin="VCC" pad="16"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="SV1" library="con-lstb" deviceset="MA08-1" device=""/>
<part name="U$1" library="esp12" deviceset="ESP8266_ESP-12" device=""/>
</parts>
<sheets>
<sheet>
<plain>
<wire x1="0" y1="0" x2="152.4" y2="0" width="0.1524" layer="94"/>
<wire x1="152.4" y1="0" x2="279.4" y2="0" width="0.1524" layer="94"/>
<wire x1="279.4" y1="0" x2="279.4" y2="38.1" width="0.1524" layer="94"/>
<wire x1="279.4" y1="38.1" x2="279.4" y2="196.85" width="0.1524" layer="94"/>
<wire x1="279.4" y1="196.85" x2="0" y2="196.85" width="0.1524" layer="94"/>
<wire x1="0" y1="196.85" x2="0" y2="0" width="0.1524" layer="94"/>
<wire x1="152.4" y1="38.1" x2="152.4" y2="0" width="0.1524" layer="94"/>
<text x="158.75" y="29.21" size="5.08" layer="94">CO2 meter with graphical display</text>
<text x="158.75" y="25.4" size="1.778" layer="94">https://github.com/semicontinuity/embedded/tree/master/target/co2-meter/</text>
<wire x1="152.4" y1="38.1" x2="279.4" y2="38.1" width="0.1524" layer="94"/>
</plain>
<instances>
<instance part="SV1" gate="1" x="246.38" y="167.64" rot="R180"/>
<instance part="U$1" gate="G$1" x="139.7" y="114.3"/>
</instances>
<busses>
</busses>
<nets>
<net name="RST" class="0">
<segment>
<pinref part="SV1" gate="1" pin="1"/>
<wire x1="238.76" y1="175.26" x2="228.6" y2="175.26" width="0.1524" layer="91"/>
<label x="228.6" y="175.26" size="1.778" layer="95"/>
</segment>
</net>
<net name="CE" class="0">
<segment>
<pinref part="SV1" gate="1" pin="2"/>
<wire x1="238.76" y1="172.72" x2="228.6" y2="172.72" width="0.1524" layer="91"/>
<label x="228.6" y="172.72" size="1.778" layer="95"/>
</segment>
</net>
<net name="DC" class="0">
<segment>
<pinref part="SV1" gate="1" pin="3"/>
<wire x1="238.76" y1="170.18" x2="228.6" y2="170.18" width="0.1524" layer="91"/>
<label x="228.6" y="170.18" size="1.778" layer="95"/>
</segment>
</net>
<net name="DIN" class="0">
<segment>
<pinref part="SV1" gate="1" pin="4"/>
<wire x1="238.76" y1="167.64" x2="228.6" y2="167.64" width="0.1524" layer="91"/>
<label x="228.6" y="167.64" size="1.778" layer="95"/>
</segment>
</net>
<net name="CLK" class="0">
<segment>
<pinref part="SV1" gate="1" pin="5"/>
<wire x1="238.76" y1="165.1" x2="228.6" y2="165.1" width="0.1524" layer="91"/>
<label x="228.6" y="165.1" size="1.778" layer="95"/>
</segment>
</net>
<net name="VDD" class="0">
<segment>
<pinref part="SV1" gate="1" pin="6"/>
<wire x1="238.76" y1="162.56" x2="228.6" y2="162.56" width="0.1524" layer="91"/>
<label x="228.6" y="162.56" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U$1" gate="G$1" pin="VCC"/>
<wire x1="116.84" y1="104.14" x2="106.68" y2="104.14" width="0.1524" layer="91"/>
<label x="109.22" y="104.14" size="1.778" layer="95"/>
</segment>
</net>
<net name="BL" class="0">
<segment>
<pinref part="SV1" gate="1" pin="7"/>
<wire x1="238.76" y1="160.02" x2="228.6" y2="160.02" width="0.1524" layer="91"/>
<label x="228.6" y="160.02" size="1.778" layer="95"/>
</segment>
</net>
<net name="GND" class="0">
<segment>
<pinref part="SV1" gate="1" pin="8"/>
<wire x1="238.76" y1="157.48" x2="228.6" y2="157.48" width="0.1524" layer="91"/>
<label x="228.6" y="157.48" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U$1" gate="G$1" pin="GND"/>
<wire x1="147.32" y1="104.14" x2="157.48" y2="104.14" width="0.1524" layer="91"/>
<label x="149.86" y="104.14" size="1.778" layer="95"/>
</segment>
</net>
<net name="N$2" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="GPIO15"/>
<wire x1="147.32" y1="106.68" x2="157.48" y2="106.68" width="0.1524" layer="91"/>
<label x="149.86" y="106.68" size="1.778" layer="95"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="GPIO2"/>
<wire x1="147.32" y1="109.22" x2="157.48" y2="109.22" width="0.1524" layer="91"/>
<label x="149.86" y="109.22" size="1.778" layer="95"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="GPIO0"/>
<wire x1="147.32" y1="111.76" x2="157.48" y2="111.76" width="0.1524" layer="91"/>
<label x="149.86" y="111.76" size="1.778" layer="95"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="GPIO5"/>
<wire x1="147.32" y1="114.3" x2="157.48" y2="114.3" width="0.1524" layer="91"/>
<label x="149.86" y="114.3" size="1.778" layer="95"/>
</segment>
</net>
<net name="N$6" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="GPIO4"/>
<wire x1="147.32" y1="116.84" x2="157.48" y2="116.84" width="0.1524" layer="91"/>
<label x="149.86" y="116.84" size="1.778" layer="95"/>
</segment>
</net>
<net name="N$7" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="RXD"/>
<wire x1="147.32" y1="119.38" x2="157.48" y2="119.38" width="0.1524" layer="91"/>
<label x="149.86" y="119.38" size="1.778" layer="95"/>
</segment>
</net>
<net name="N$8" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="TXD"/>
<wire x1="147.32" y1="121.92" x2="157.48" y2="121.92" width="0.1524" layer="91"/>
<label x="149.86" y="121.92" size="1.778" layer="95"/>
</segment>
</net>
<net name="N$10" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="GPIO13"/>
<wire x1="116.84" y1="106.68" x2="106.68" y2="106.68" width="0.1524" layer="91"/>
<label x="109.22" y="106.68" size="1.778" layer="95"/>
</segment>
</net>
<net name="N$11" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="GPIO12"/>
<wire x1="116.84" y1="109.22" x2="106.68" y2="109.22" width="0.1524" layer="91"/>
<label x="109.22" y="109.22" size="1.778" layer="95"/>
</segment>
</net>
<net name="N$12" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="GPIO14"/>
<wire x1="116.84" y1="111.76" x2="106.68" y2="111.76" width="0.1524" layer="91"/>
<label x="109.22" y="111.76" size="1.778" layer="95"/>
</segment>
</net>
<net name="N$13" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="GPIO16"/>
<wire x1="116.84" y1="114.3" x2="106.68" y2="114.3" width="0.1524" layer="91"/>
<label x="109.22" y="114.3" size="1.778" layer="95"/>
</segment>
</net>
<net name="N$14" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="CH_PD"/>
<wire x1="116.84" y1="116.84" x2="106.68" y2="116.84" width="0.1524" layer="91"/>
<label x="109.22" y="116.84" size="1.778" layer="95"/>
</segment>
</net>
<net name="N$15" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="ADC"/>
<wire x1="116.84" y1="119.38" x2="106.68" y2="119.38" width="0.1524" layer="91"/>
<label x="109.22" y="119.38" size="1.778" layer="95"/>
</segment>
</net>
<net name="N$16" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="REST"/>
<wire x1="116.84" y1="121.92" x2="106.68" y2="121.92" width="0.1524" layer="91"/>
<label x="109.22" y="121.92" size="1.778" layer="95"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
