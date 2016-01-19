<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="7.5.0">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
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
<layer number="25" name="tNames" color="14" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="11" fill="1" visible="no" active="no"/>
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
<layer number="51" name="tDocu" color="13" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
<layer number="100" name="Muster" color="7" fill="1" visible="no" active="no"/>
<layer number="101" name="Bemassung" color="7" fill="1" visible="yes" active="yes"/>
<layer number="200" name="200bmp" color="1" fill="10" visible="no" active="no"/>
<layer number="231" name="Eagle3D_PG1" color="7" fill="1" visible="yes" active="yes"/>
<layer number="232" name="Eagle3D_PG2" color="7" fill="1" visible="yes" active="yes"/>
<layer number="233" name="Eagle3D_PG3" color="7" fill="1" visible="yes" active="yes"/>
<layer number="250" name="Descript" color="3" fill="1" visible="yes" active="yes"/>
<layer number="251" name="SMDround" color="12" fill="11" visible="yes" active="yes"/>
<layer number="254" name="OrgLBR" color="7" fill="1" visible="no" active="yes"/>
</layers>
<schematic>
<libraries>
<library name="atmel">
<description>&lt;b&gt;AVR Devices&lt;/b&gt;&lt;p&gt;
Configurable logic, microcontrollers, nonvolatile memories&lt;p&gt;
Based on the following sources:&lt;p&gt;
&lt;ul&gt;
&lt;li&gt;www.atmel.com
&lt;li&gt;CD-ROM : Configurable Logic Microcontroller Nonvolatile Memory
&lt;li&gt;CadSoft download site, www.cadsoft.de or www.cadsoftusa.com , file at90smcu_v400.zip
&lt;li&gt;avr.lbr
&lt;/ul&gt;
&lt;author&gt;Revised by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="DIL32">
<description>&lt;b&gt;Dual In Line&lt;/b&gt;</description>
<wire x1="-21.336" y1="-1.27" x2="-21.336" y2="-6.604" width="0.1524" layer="21"/>
<wire x1="-21.336" y1="1.27" x2="-21.336" y2="-1.27" width="0.1524" layer="21" curve="-180"/>
<wire x1="21.336" y1="-6.604" x2="21.336" y2="6.604" width="0.1524" layer="21"/>
<wire x1="-21.336" y1="-6.604" x2="21.336" y2="-6.604" width="0.1524" layer="21"/>
<wire x1="-21.336" y1="6.604" x2="-21.336" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-21.336" y1="6.604" x2="21.336" y2="6.604" width="0.1524" layer="21"/>
<pad name="1" x="-19.05" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="2" x="-16.51" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="3" x="-13.97" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="4" x="-11.43" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="5" x="-8.89" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="6" x="-6.35" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="7" x="-3.81" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="8" x="-1.27" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="9" x="1.27" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="10" x="3.81" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="11" x="6.35" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="12" x="8.89" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="13" x="11.43" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="14" x="13.97" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="15" x="16.51" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="16" x="19.05" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="17" x="19.05" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="18" x="16.51" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="19" x="13.97" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="20" x="11.43" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="21" x="8.89" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="22" x="6.35" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="23" x="3.81" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="24" x="1.27" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="25" x="-1.27" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="26" x="-3.81" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="27" x="-6.35" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="28" x="-8.89" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="29" x="-11.43" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="30" x="-13.97" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="31" x="-16.51" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="32" x="-19.05" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<text x="-21.717" y="-6.35" size="1.778" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="-16.51" y="-0.9652" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
</package>
<package name="SO32X">
<description>&lt;b&gt;SMALL OUTLINE INTEGRATED CIRCUIT&lt;/b&gt;&lt;p&gt;
extra wide body 8.9 mm/JEDEC MO-120AC</description>
<wire x1="10.22" y1="-4.5" x2="-10.22" y2="-4.5" width="0.2032" layer="51"/>
<wire x1="-10.22" y1="-4.5" x2="-10.22" y2="-4" width="0.2032" layer="51"/>
<wire x1="-10.22" y1="-4" x2="-10.22" y2="4.5" width="0.2032" layer="51"/>
<wire x1="-10.22" y1="4.5" x2="10.22" y2="4.5" width="0.2032" layer="51"/>
<wire x1="10.22" y1="-4" x2="-10.22" y2="-4" width="0.2032" layer="51"/>
<wire x1="10.22" y1="4.5" x2="10.22" y2="-4" width="0.2032" layer="51"/>
<wire x1="10.22" y1="-4" x2="10.22" y2="-4.5" width="0.2032" layer="51"/>
<smd name="2" x="-8.255" y="-5.4" dx="0.6" dy="2.2" layer="1"/>
<smd name="13" x="5.715" y="-5.4" dx="0.6" dy="2.2" layer="1"/>
<smd name="1" x="-9.525" y="-5.4" dx="0.6" dy="2.2" layer="1"/>
<smd name="3" x="-6.985" y="-5.4" dx="0.6" dy="2.2" layer="1"/>
<smd name="4" x="-5.715" y="-5.4" dx="0.6" dy="2.2" layer="1"/>
<smd name="14" x="6.985" y="-5.4" dx="0.6" dy="2.2" layer="1"/>
<smd name="12" x="4.445" y="-5.4" dx="0.6" dy="2.2" layer="1"/>
<smd name="11" x="3.175" y="-5.4" dx="0.6" dy="2.2" layer="1"/>
<smd name="6" x="-3.175" y="-5.4" dx="0.6" dy="2.2" layer="1"/>
<smd name="9" x="0.635" y="-5.4" dx="0.6" dy="2.2" layer="1"/>
<smd name="5" x="-4.445" y="-5.4" dx="0.6" dy="2.2" layer="1"/>
<smd name="7" x="-1.905" y="-5.4" dx="0.6" dy="2.2" layer="1"/>
<smd name="10" x="1.905" y="-5.4" dx="0.6" dy="2.2" layer="1"/>
<smd name="8" x="-0.635" y="-5.4" dx="0.6" dy="2.2" layer="1"/>
<smd name="15" x="8.255" y="-5.4" dx="0.6" dy="2.2" layer="1"/>
<smd name="16" x="9.525" y="-5.4" dx="0.6" dy="2.2" layer="1"/>
<smd name="17" x="9.525" y="5.4" dx="0.6" dy="2.2" layer="1"/>
<smd name="18" x="8.255" y="5.4" dx="0.6" dy="2.2" layer="1"/>
<smd name="19" x="6.985" y="5.4" dx="0.6" dy="2.2" layer="1"/>
<smd name="20" x="5.715" y="5.4" dx="0.6" dy="2.2" layer="1"/>
<smd name="21" x="4.445" y="5.4" dx="0.6" dy="2.2" layer="1"/>
<smd name="22" x="3.175" y="5.4" dx="0.6" dy="2.2" layer="1"/>
<smd name="23" x="1.905" y="5.4" dx="0.6" dy="2.2" layer="1"/>
<smd name="24" x="0.635" y="5.4" dx="0.6" dy="2.2" layer="1"/>
<smd name="25" x="-0.635" y="5.4" dx="0.6" dy="2.2" layer="1"/>
<smd name="26" x="-1.905" y="5.4" dx="0.6" dy="2.2" layer="1"/>
<smd name="27" x="-3.175" y="5.4" dx="0.6" dy="2.2" layer="1"/>
<smd name="28" x="-4.445" y="5.4" dx="0.6" dy="2.2" layer="1"/>
<smd name="29" x="-5.715" y="5.4" dx="0.6" dy="2.2" layer="1"/>
<smd name="30" x="-6.985" y="5.4" dx="0.6" dy="2.2" layer="1"/>
<smd name="31" x="-8.255" y="5.4" dx="0.6" dy="2.2" layer="1"/>
<smd name="32" x="-9.525" y="5.4" dx="0.6" dy="2.2" layer="1"/>
<text x="-8.255" y="1.27" size="1.27" layer="25">&gt;NAME</text>
<text x="-8.255" y="-2.54" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-9.7701" y1="-6.1199" x2="-9.2799" y2="-4.5999" layer="51"/>
<rectangle x1="-8.5001" y1="-6.1199" x2="-8.0099" y2="-4.5999" layer="51"/>
<rectangle x1="-7.2301" y1="-6.1199" x2="-6.7399" y2="-4.5999" layer="51"/>
<rectangle x1="-5.9601" y1="-6.1199" x2="-5.4699" y2="-4.5999" layer="51"/>
<rectangle x1="-4.6901" y1="-6.1199" x2="-4.1999" y2="-4.5999" layer="51"/>
<rectangle x1="-3.4201" y1="-6.1199" x2="-2.9299" y2="-4.5999" layer="51"/>
<rectangle x1="-2.1501" y1="-6.1199" x2="-1.6599" y2="-4.5999" layer="51"/>
<rectangle x1="-0.8801" y1="-6.1199" x2="-0.3899" y2="-4.5999" layer="51"/>
<rectangle x1="0.3899" y1="-6.1199" x2="0.8801" y2="-4.5999" layer="51"/>
<rectangle x1="1.6599" y1="-6.1199" x2="2.1501" y2="-4.5999" layer="51"/>
<rectangle x1="2.9299" y1="-6.1199" x2="3.4201" y2="-4.5999" layer="51"/>
<rectangle x1="4.1999" y1="-6.1199" x2="4.6901" y2="-4.5999" layer="51"/>
<rectangle x1="5.4699" y1="-6.1199" x2="5.9601" y2="-4.5999" layer="51"/>
<rectangle x1="6.7399" y1="-6.1199" x2="7.2301" y2="-4.5999" layer="51"/>
<rectangle x1="8.0099" y1="-6.1199" x2="8.5001" y2="-4.5999" layer="51"/>
<rectangle x1="9.2799" y1="-6.1199" x2="9.7701" y2="-4.5999" layer="51"/>
<rectangle x1="9.2799" y1="4.5999" x2="9.7701" y2="6.1199" layer="51"/>
<rectangle x1="8.0099" y1="4.5999" x2="8.5001" y2="6.1199" layer="51"/>
<rectangle x1="6.7399" y1="4.5999" x2="7.2301" y2="6.1199" layer="51"/>
<rectangle x1="5.4699" y1="4.5999" x2="5.9601" y2="6.1199" layer="51"/>
<rectangle x1="4.1999" y1="4.5999" x2="4.6901" y2="6.1199" layer="51"/>
<rectangle x1="2.9299" y1="4.5999" x2="3.4201" y2="6.1199" layer="51"/>
<rectangle x1="1.6599" y1="4.5999" x2="2.1501" y2="6.1199" layer="51"/>
<rectangle x1="0.3899" y1="4.5999" x2="0.8801" y2="6.1199" layer="51"/>
<rectangle x1="-0.8801" y1="4.5999" x2="-0.3899" y2="6.1199" layer="51"/>
<rectangle x1="-2.1501" y1="4.5999" x2="-1.6599" y2="6.1199" layer="51"/>
<rectangle x1="-3.4201" y1="4.5999" x2="-2.9299" y2="6.1199" layer="51"/>
<rectangle x1="-4.6901" y1="4.5999" x2="-4.1999" y2="6.1199" layer="51"/>
<rectangle x1="-5.9601" y1="4.5999" x2="-5.4699" y2="6.1199" layer="51"/>
<rectangle x1="-7.2301" y1="4.5999" x2="-6.7399" y2="6.1199" layer="51"/>
<rectangle x1="-8.5001" y1="4.5999" x2="-8.0099" y2="6.1199" layer="51"/>
<rectangle x1="-9.7701" y1="4.5999" x2="-9.2799" y2="6.1199" layer="51"/>
</package>
<package name="PLCC32R">
<description>&lt;b&gt;PLASTIC LEADED CHIP CARRIER&lt;/b&gt;&lt;p&gt;
rectangle</description>
<wire x1="-5.61" y1="-6.93" x2="5.61" y2="-6.93" width="0.2032" layer="51"/>
<wire x1="5.61" y1="-6.93" x2="5.61" y2="6.93" width="0.2032" layer="51"/>
<wire x1="5.61" y1="6.93" x2="-4.77" y2="6.93" width="0.2032" layer="51"/>
<wire x1="-4.77" y1="6.93" x2="-5.61" y2="6.09" width="0.2032" layer="51"/>
<wire x1="-5.61" y1="6.09" x2="-5.61" y2="-6.93" width="0.2032" layer="51"/>
<circle x="0" y="5.4" radius="0.3" width="0.6096" layer="51"/>
<smd name="1" x="0" y="6.9" dx="0.6" dy="2.2" layer="1"/>
<smd name="2" x="-1.27" y="6.9" dx="0.6" dy="2.2" layer="1"/>
<smd name="3" x="-2.54" y="6.9" dx="0.6" dy="2.2" layer="1"/>
<smd name="4" x="-3.81" y="6.9" dx="0.6" dy="2.2" layer="1"/>
<smd name="6" x="-5.7" y="3.81" dx="2.2" dy="0.6" layer="1"/>
<smd name="7" x="-5.7" y="2.54" dx="2.2" dy="0.6" layer="1"/>
<smd name="8" x="-5.7" y="1.27" dx="2.2" dy="0.6" layer="1"/>
<smd name="9" x="-5.7" y="0" dx="2.2" dy="0.6" layer="1"/>
<smd name="10" x="-5.7" y="-1.27" dx="2.2" dy="0.6" layer="1"/>
<smd name="11" x="-5.7" y="-2.54" dx="2.2" dy="0.6" layer="1"/>
<smd name="12" x="-5.7" y="-3.81" dx="2.2" dy="0.6" layer="1"/>
<smd name="5" x="-5.7" y="5.08" dx="2.2" dy="0.6" layer="1"/>
<smd name="13" x="-5.7" y="-5.08" dx="2.2" dy="0.6" layer="1"/>
<smd name="14" x="-3.81" y="-6.9" dx="0.6" dy="2.2" layer="1"/>
<smd name="15" x="-2.54" y="-6.9" dx="0.6" dy="2.2" layer="1"/>
<smd name="16" x="-1.27" y="-6.9" dx="0.6" dy="2.2" layer="1"/>
<smd name="17" x="0" y="-6.9" dx="0.6" dy="2.2" layer="1"/>
<smd name="18" x="1.27" y="-6.9" dx="0.6" dy="2.2" layer="1"/>
<smd name="19" x="2.54" y="-6.9" dx="0.6" dy="2.2" layer="1"/>
<smd name="20" x="3.81" y="-6.9" dx="0.6" dy="2.2" layer="1"/>
<smd name="21" x="5.7" y="-5.08" dx="2.2" dy="0.6" layer="1"/>
<smd name="22" x="5.7" y="-3.81" dx="2.2" dy="0.6" layer="1"/>
<smd name="23" x="5.7" y="-2.54" dx="2.2" dy="0.6" layer="1"/>
<smd name="24" x="5.7" y="-1.27" dx="2.2" dy="0.6" layer="1"/>
<smd name="25" x="5.7" y="0" dx="2.2" dy="0.6" layer="1"/>
<smd name="26" x="5.7" y="1.27" dx="2.2" dy="0.6" layer="1"/>
<smd name="27" x="5.7" y="2.54" dx="2.2" dy="0.6" layer="1"/>
<smd name="28" x="5.7" y="3.81" dx="2.2" dy="0.6" layer="1"/>
<smd name="29" x="5.7" y="5.08" dx="2.2" dy="0.6" layer="1"/>
<smd name="30" x="3.81" y="6.9" dx="0.6" dy="2.2" layer="1"/>
<smd name="31" x="2.54" y="6.9" dx="0.6" dy="2.2" layer="1"/>
<smd name="32" x="1.27" y="6.9" dx="0.6" dy="2.2" layer="1"/>
<text x="-2.825" y="5.2751" size="1.778" layer="25" rot="R270">&gt;NAME</text>
<text x="0.6949" y="5.2451" size="1.778" layer="27" rot="R270">&gt;VALUE</text>
<rectangle x1="-0.2601" y1="6.9499" x2="0.27" y2="7.5301" layer="51"/>
<rectangle x1="-1.5301" y1="6.9499" x2="-1" y2="7.5301" layer="51"/>
<rectangle x1="-2.8001" y1="6.9499" x2="-2.27" y2="7.5301" layer="51"/>
<rectangle x1="-4.0701" y1="6.9499" x2="-3.54" y2="7.5301" layer="51"/>
<rectangle x1="-6.3299" y1="4.8199" x2="-5.7501" y2="5.35" layer="51"/>
<rectangle x1="-6.3299" y1="3.5499" x2="-5.7501" y2="4.08" layer="51"/>
<rectangle x1="-6.3299" y1="2.2799" x2="-5.7501" y2="2.81" layer="51"/>
<rectangle x1="-6.3299" y1="1.0099" x2="-5.7501" y2="1.54" layer="51"/>
<rectangle x1="-6.3299" y1="-0.2601" x2="-5.7501" y2="0.27" layer="51"/>
<rectangle x1="-6.3299" y1="-1.5301" x2="-5.7501" y2="-1" layer="51"/>
<rectangle x1="-6.3299" y1="-2.8001" x2="-5.7501" y2="-2.27" layer="51"/>
<rectangle x1="-6.3299" y1="-4.0701" x2="-5.7501" y2="-3.54" layer="51"/>
<rectangle x1="-6.3299" y1="-5.3401" x2="-5.7501" y2="-4.81" layer="51"/>
<rectangle x1="-4.08" y1="-7.5301" x2="-3.5499" y2="-6.9499" layer="51"/>
<rectangle x1="-2.81" y1="-7.5301" x2="-2.2799" y2="-6.9499" layer="51"/>
<rectangle x1="-1.54" y1="-7.5301" x2="-1.0099" y2="-6.9499" layer="51"/>
<rectangle x1="-0.27" y1="-7.5301" x2="0.2601" y2="-6.9499" layer="51"/>
<rectangle x1="1" y1="-7.5301" x2="1.5301" y2="-6.9499" layer="51"/>
<rectangle x1="2.27" y1="-7.5301" x2="2.8001" y2="-6.9499" layer="51"/>
<rectangle x1="3.54" y1="-7.5301" x2="4.0701" y2="-6.9499" layer="51"/>
<rectangle x1="5.7501" y1="-5.35" x2="6.3299" y2="-4.8199" layer="51"/>
<rectangle x1="5.7501" y1="-4.08" x2="6.3299" y2="-3.5499" layer="51"/>
<rectangle x1="5.7501" y1="-2.81" x2="6.3299" y2="-2.2799" layer="51"/>
<rectangle x1="5.7501" y1="-1.54" x2="6.3299" y2="-1.0099" layer="51"/>
<rectangle x1="5.7501" y1="-0.27" x2="6.3299" y2="0.2601" layer="51"/>
<rectangle x1="5.7501" y1="1" x2="6.3299" y2="1.5301" layer="51"/>
<rectangle x1="5.7501" y1="2.27" x2="6.3299" y2="2.8001" layer="51"/>
<rectangle x1="5.7501" y1="3.54" x2="6.3299" y2="4.0701" layer="51"/>
<rectangle x1="5.7501" y1="4.81" x2="6.3299" y2="5.3401" layer="51"/>
<rectangle x1="3.5499" y1="6.9499" x2="4.08" y2="7.5301" layer="51"/>
<rectangle x1="2.2799" y1="6.9499" x2="2.81" y2="7.5301" layer="51"/>
<rectangle x1="1.0099" y1="6.9499" x2="1.54" y2="7.5301" layer="51"/>
</package>
<package name="TSOP32">
<description>&lt;b&gt;TSOP32&lt;/b&gt;&lt;p&gt;
thin small outline package</description>
<wire x1="3.995" y1="9.185" x2="3.995" y2="-9.195" width="0.2032" layer="51"/>
<wire x1="3.995" y1="-9.195" x2="-3.995" y2="-9.195" width="0.2032" layer="51"/>
<wire x1="-3.995" y1="-9.195" x2="-3.995" y2="9.185" width="0.2032" layer="51"/>
<wire x1="-3.995" y1="9.185" x2="3.995" y2="9.185" width="0.2032" layer="51"/>
<smd name="1" x="-3.75" y="-9.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="2" x="-3.25" y="-9.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="3" x="-2.75" y="-9.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="4" x="-2.25" y="-9.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="5" x="-1.75" y="-9.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="6" x="-1.25" y="-9.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="7" x="-0.75" y="-9.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="8" x="-0.25" y="-9.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="9" x="0.25" y="-9.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="10" x="0.75" y="-9.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="11" x="1.25" y="-9.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="12" x="1.75" y="-9.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="13" x="2.25" y="-9.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="14" x="2.75" y="-9.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="15" x="3.25" y="-9.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="16" x="3.75" y="-9.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="17" x="3.75" y="9.59" dx="0.3" dy="1.6" layer="1"/>
<smd name="18" x="3.25" y="9.59" dx="0.3" dy="1.6" layer="1"/>
<smd name="19" x="2.75" y="9.59" dx="0.3" dy="1.6" layer="1"/>
<smd name="20" x="2.25" y="9.59" dx="0.3" dy="1.6" layer="1"/>
<smd name="21" x="1.75" y="9.59" dx="0.3" dy="1.6" layer="1"/>
<smd name="22" x="1.25" y="9.59" dx="0.3" dy="1.6" layer="1"/>
<smd name="23" x="0.75" y="9.59" dx="0.3" dy="1.6" layer="1"/>
<smd name="24" x="0.25" y="9.59" dx="0.3" dy="1.6" layer="1"/>
<smd name="25" x="-0.25" y="9.59" dx="0.3" dy="1.6" layer="1"/>
<smd name="26" x="-0.75" y="9.59" dx="0.3" dy="1.6" layer="1"/>
<smd name="27" x="-1.25" y="9.59" dx="0.3" dy="1.6" layer="1"/>
<smd name="28" x="-1.75" y="9.59" dx="0.3" dy="1.6" layer="1"/>
<smd name="29" x="-2.25" y="9.59" dx="0.3" dy="1.6" layer="1"/>
<smd name="30" x="-2.75" y="9.59" dx="0.3" dy="1.6" layer="1"/>
<smd name="31" x="-3.25" y="9.59" dx="0.3" dy="1.6" layer="1"/>
<smd name="32" x="-3.75" y="9.59" dx="0.3" dy="1.6" layer="1"/>
<text x="-1.635" y="-3.175" size="1.27" layer="25" rot="R90">&gt;NAME</text>
<text x="0.905" y="-3.81" size="1.27" layer="27" rot="R90">&gt;VALUE</text>
<text x="-3.7313" y="-8.48" size="1.016" layer="21" font="vector">1</text>
<rectangle x1="-3.8999" y1="-10.1001" x2="-3.5999" y2="-9.2499" layer="51"/>
<rectangle x1="-3.4" y1="-10.1001" x2="-3.1001" y2="-9.2499" layer="51"/>
<rectangle x1="-2.8999" y1="-10.1001" x2="-2.5999" y2="-9.2499" layer="51"/>
<rectangle x1="-2.4" y1="-10.1001" x2="-2.1001" y2="-9.2499" layer="51"/>
<rectangle x1="-1.8999" y1="-10.1001" x2="-1.5999" y2="-9.2499" layer="51"/>
<rectangle x1="-1.4" y1="-10.1001" x2="-1.1001" y2="-9.2499" layer="51"/>
<rectangle x1="-0.8999" y1="-10.1001" x2="-0.5999" y2="-9.2499" layer="51"/>
<rectangle x1="-0.4001" y1="-10.1001" x2="-0.1001" y2="-9.2499" layer="51"/>
<rectangle x1="0.1001" y1="-10.1001" x2="0.4001" y2="-9.2499" layer="51"/>
<rectangle x1="0.5999" y1="-10.1001" x2="0.8999" y2="-9.2499" layer="51"/>
<rectangle x1="1.1001" y1="-10.1001" x2="1.4" y2="-9.2499" layer="51"/>
<rectangle x1="1.5999" y1="-10.1001" x2="1.8999" y2="-9.2499" layer="51"/>
<rectangle x1="2.1001" y1="-10.1001" x2="2.4" y2="-9.2499" layer="51"/>
<rectangle x1="2.5999" y1="-10.1001" x2="2.8999" y2="-9.2499" layer="51"/>
<rectangle x1="3.1001" y1="-10.1001" x2="3.4" y2="-9.2499" layer="51"/>
<rectangle x1="3.5999" y1="-10.1001" x2="3.8999" y2="-9.2499" layer="51"/>
<rectangle x1="3.5999" y1="9.2399" x2="3.8999" y2="10.0901" layer="51"/>
<rectangle x1="3.1001" y1="9.2399" x2="3.4" y2="10.0901" layer="51"/>
<rectangle x1="2.5999" y1="9.2399" x2="2.8999" y2="10.0901" layer="51"/>
<rectangle x1="2.1001" y1="9.2399" x2="2.4" y2="10.0901" layer="51"/>
<rectangle x1="1.5999" y1="9.2399" x2="1.8999" y2="10.0901" layer="51"/>
<rectangle x1="1.1001" y1="9.2399" x2="1.4" y2="10.0901" layer="51"/>
<rectangle x1="0.5999" y1="9.2399" x2="0.8999" y2="10.0901" layer="51"/>
<rectangle x1="0.1001" y1="9.2399" x2="0.4001" y2="10.0901" layer="51"/>
<rectangle x1="-0.4001" y1="9.2399" x2="-0.1001" y2="10.0901" layer="51"/>
<rectangle x1="-0.8999" y1="9.2399" x2="-0.5999" y2="10.0901" layer="51"/>
<rectangle x1="-1.4" y1="9.2399" x2="-1.1001" y2="10.0901" layer="51"/>
<rectangle x1="-1.8999" y1="9.2399" x2="-1.5999" y2="10.0901" layer="51"/>
<rectangle x1="-2.4" y1="9.2399" x2="-2.1001" y2="10.0901" layer="51"/>
<rectangle x1="-2.8999" y1="9.2399" x2="-2.5999" y2="10.0901" layer="51"/>
<rectangle x1="-3.4" y1="9.2399" x2="-3.1001" y2="10.0901" layer="51"/>
<rectangle x1="-3.8999" y1="9.2399" x2="-3.5999" y2="10.0901" layer="51"/>
</package>
</packages>
<symbols>
<symbol name="27C080">
<wire x1="-7.62" y1="-30.48" x2="7.62" y2="-30.48" width="0.4064" layer="94"/>
<wire x1="7.62" y1="-30.48" x2="7.62" y2="30.48" width="0.4064" layer="94"/>
<wire x1="7.62" y1="30.48" x2="-7.62" y2="30.48" width="0.4064" layer="94"/>
<wire x1="-7.62" y1="30.48" x2="-7.62" y2="-30.48" width="0.4064" layer="94"/>
<text x="-7.62" y="31.115" size="1.778" layer="95">&gt;NAME</text>
<text x="-7.62" y="-33.02" size="1.778" layer="96">&gt;VALUE</text>
<pin name="A16" x="-10.16" y="-12.7" length="short" direction="in"/>
<pin name="A15" x="-10.16" y="-10.16" length="short" direction="in"/>
<pin name="A12" x="-10.16" y="-2.54" length="short" direction="in"/>
<pin name="A7" x="-10.16" y="10.16" length="short" direction="in"/>
<pin name="A6" x="-10.16" y="12.7" length="short" direction="in"/>
<pin name="A5" x="-10.16" y="15.24" length="short" direction="in"/>
<pin name="A4" x="-10.16" y="17.78" length="short" direction="in"/>
<pin name="A3" x="-10.16" y="20.32" length="short" direction="in"/>
<pin name="A2" x="-10.16" y="22.86" length="short" direction="in"/>
<pin name="A1" x="-10.16" y="25.4" length="short" direction="in"/>
<pin name="A0" x="-10.16" y="27.94" length="short" direction="in"/>
<pin name="O0" x="10.16" y="27.94" length="short" direction="hiz" rot="R180"/>
<pin name="O1" x="10.16" y="25.4" length="short" direction="hiz" rot="R180"/>
<pin name="O2" x="10.16" y="22.86" length="short" direction="hiz" rot="R180"/>
<pin name="O3" x="10.16" y="20.32" length="short" direction="hiz" rot="R180"/>
<pin name="O4" x="10.16" y="17.78" length="short" direction="hiz" rot="R180"/>
<pin name="O5" x="10.16" y="15.24" length="short" direction="hiz" rot="R180"/>
<pin name="O6" x="10.16" y="12.7" length="short" direction="hiz" rot="R180"/>
<pin name="O7" x="10.16" y="10.16" length="short" direction="hiz" rot="R180"/>
<pin name="!CE" x="-10.16" y="-25.4" length="short" direction="in"/>
<pin name="A10" x="-10.16" y="2.54" length="short" direction="in"/>
<pin name="!OE!VPP" x="-10.16" y="-27.94" length="short" direction="in"/>
<pin name="A11" x="-10.16" y="0" length="short" direction="in"/>
<pin name="A9" x="-10.16" y="5.08" length="short" direction="in"/>
<pin name="A8" x="-10.16" y="7.62" length="short" direction="in"/>
<pin name="A13" x="-10.16" y="-5.08" length="short" direction="in"/>
<pin name="A14" x="-10.16" y="-7.62" length="short" direction="in"/>
<pin name="A17" x="-10.16" y="-15.24" length="short" direction="in"/>
<pin name="A18" x="-10.16" y="-17.78" length="short" direction="in"/>
<pin name="A19" x="-10.16" y="-20.32" length="short" direction="in"/>
</symbol>
<symbol name="VCCGND">
<text x="2.54" y="0.635" size="1.778" layer="95">&gt;NAME</text>
<pin name="GND" x="0" y="-10.16" length="short" direction="pwr" rot="R90"/>
<pin name="VCC" x="0" y="10.16" length="short" direction="pwr" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="27C080" prefix="IC">
<description>&lt;b&gt;8-Megabit (1Mx8) OTP EPROM&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="27C080" x="0" y="0"/>
<gate name="P" symbol="VCCGND" x="15.24" y="-10.16" addlevel="request"/>
</gates>
<devices>
<device name="32P6" package="DIL32">
<connects>
<connect gate="G$1" pin="!CE" pad="22"/>
<connect gate="G$1" pin="!OE!VPP" pad="24"/>
<connect gate="G$1" pin="A0" pad="12"/>
<connect gate="G$1" pin="A1" pad="11"/>
<connect gate="G$1" pin="A10" pad="23"/>
<connect gate="G$1" pin="A11" pad="25"/>
<connect gate="G$1" pin="A12" pad="4"/>
<connect gate="G$1" pin="A13" pad="28"/>
<connect gate="G$1" pin="A14" pad="29"/>
<connect gate="G$1" pin="A15" pad="3"/>
<connect gate="G$1" pin="A16" pad="2"/>
<connect gate="G$1" pin="A17" pad="30"/>
<connect gate="G$1" pin="A18" pad="31"/>
<connect gate="G$1" pin="A19" pad="1"/>
<connect gate="G$1" pin="A2" pad="10"/>
<connect gate="G$1" pin="A3" pad="9"/>
<connect gate="G$1" pin="A4" pad="8"/>
<connect gate="G$1" pin="A5" pad="7"/>
<connect gate="G$1" pin="A6" pad="6"/>
<connect gate="G$1" pin="A7" pad="5"/>
<connect gate="G$1" pin="A8" pad="27"/>
<connect gate="G$1" pin="A9" pad="26"/>
<connect gate="G$1" pin="O0" pad="13"/>
<connect gate="G$1" pin="O1" pad="14"/>
<connect gate="G$1" pin="O2" pad="15"/>
<connect gate="G$1" pin="O3" pad="17"/>
<connect gate="G$1" pin="O4" pad="18"/>
<connect gate="G$1" pin="O5" pad="19"/>
<connect gate="G$1" pin="O6" pad="20"/>
<connect gate="G$1" pin="O7" pad="21"/>
<connect gate="P" pin="GND" pad="16"/>
<connect gate="P" pin="VCC" pad="32"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="AT27C080-90PU" constant="no"/>
<attribute name="OC_FARNELL" value="1455026" constant="no"/>
<attribute name="OC_NEWARK" value="58M3824" constant="no"/>
</technology>
</technologies>
</device>
<device name="R" package="SO32X">
<connects>
<connect gate="G$1" pin="!CE" pad="22"/>
<connect gate="G$1" pin="!OE!VPP" pad="24"/>
<connect gate="G$1" pin="A0" pad="12"/>
<connect gate="G$1" pin="A1" pad="11"/>
<connect gate="G$1" pin="A10" pad="23"/>
<connect gate="G$1" pin="A11" pad="25"/>
<connect gate="G$1" pin="A12" pad="4"/>
<connect gate="G$1" pin="A13" pad="28"/>
<connect gate="G$1" pin="A14" pad="29"/>
<connect gate="G$1" pin="A15" pad="3"/>
<connect gate="G$1" pin="A16" pad="2"/>
<connect gate="G$1" pin="A17" pad="30"/>
<connect gate="G$1" pin="A18" pad="31"/>
<connect gate="G$1" pin="A19" pad="1"/>
<connect gate="G$1" pin="A2" pad="10"/>
<connect gate="G$1" pin="A3" pad="9"/>
<connect gate="G$1" pin="A4" pad="8"/>
<connect gate="G$1" pin="A5" pad="7"/>
<connect gate="G$1" pin="A6" pad="6"/>
<connect gate="G$1" pin="A7" pad="5"/>
<connect gate="G$1" pin="A8" pad="27"/>
<connect gate="G$1" pin="A9" pad="26"/>
<connect gate="G$1" pin="O0" pad="13"/>
<connect gate="G$1" pin="O1" pad="14"/>
<connect gate="G$1" pin="O2" pad="15"/>
<connect gate="G$1" pin="O3" pad="17"/>
<connect gate="G$1" pin="O4" pad="18"/>
<connect gate="G$1" pin="O5" pad="19"/>
<connect gate="G$1" pin="O6" pad="20"/>
<connect gate="G$1" pin="O7" pad="21"/>
<connect gate="P" pin="GND" pad="16"/>
<connect gate="P" pin="VCC" pad="32"/>
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
<device name="J" package="PLCC32R">
<connects>
<connect gate="G$1" pin="!CE" pad="22"/>
<connect gate="G$1" pin="!OE!VPP" pad="24"/>
<connect gate="G$1" pin="A0" pad="12"/>
<connect gate="G$1" pin="A1" pad="11"/>
<connect gate="G$1" pin="A10" pad="23"/>
<connect gate="G$1" pin="A11" pad="25"/>
<connect gate="G$1" pin="A12" pad="4"/>
<connect gate="G$1" pin="A13" pad="28"/>
<connect gate="G$1" pin="A14" pad="29"/>
<connect gate="G$1" pin="A15" pad="3"/>
<connect gate="G$1" pin="A16" pad="2"/>
<connect gate="G$1" pin="A17" pad="30"/>
<connect gate="G$1" pin="A18" pad="31"/>
<connect gate="G$1" pin="A19" pad="1"/>
<connect gate="G$1" pin="A2" pad="10"/>
<connect gate="G$1" pin="A3" pad="9"/>
<connect gate="G$1" pin="A4" pad="8"/>
<connect gate="G$1" pin="A5" pad="7"/>
<connect gate="G$1" pin="A6" pad="6"/>
<connect gate="G$1" pin="A7" pad="5"/>
<connect gate="G$1" pin="A8" pad="27"/>
<connect gate="G$1" pin="A9" pad="26"/>
<connect gate="G$1" pin="O0" pad="13"/>
<connect gate="G$1" pin="O1" pad="14"/>
<connect gate="G$1" pin="O2" pad="15"/>
<connect gate="G$1" pin="O3" pad="17"/>
<connect gate="G$1" pin="O4" pad="18"/>
<connect gate="G$1" pin="O5" pad="19"/>
<connect gate="G$1" pin="O6" pad="20"/>
<connect gate="G$1" pin="O7" pad="21"/>
<connect gate="P" pin="GND" pad="16"/>
<connect gate="P" pin="VCC" pad="32"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="AT27C080-90JU" constant="no"/>
<attribute name="OC_FARNELL" value="1455025" constant="no"/>
<attribute name="OC_NEWARK" value="58M3823" constant="no"/>
</technology>
</technologies>
</device>
<device name="T" package="TSOP32">
<connects>
<connect gate="G$1" pin="!CE" pad="30"/>
<connect gate="G$1" pin="!OE!VPP" pad="32"/>
<connect gate="G$1" pin="A0" pad="20"/>
<connect gate="G$1" pin="A1" pad="19"/>
<connect gate="G$1" pin="A10" pad="31"/>
<connect gate="G$1" pin="A11" pad="1"/>
<connect gate="G$1" pin="A12" pad="12"/>
<connect gate="G$1" pin="A13" pad="4"/>
<connect gate="G$1" pin="A14" pad="5"/>
<connect gate="G$1" pin="A15" pad="11"/>
<connect gate="G$1" pin="A16" pad="10"/>
<connect gate="G$1" pin="A17" pad="6"/>
<connect gate="G$1" pin="A18" pad="7"/>
<connect gate="G$1" pin="A19" pad="9"/>
<connect gate="G$1" pin="A2" pad="18"/>
<connect gate="G$1" pin="A3" pad="17"/>
<connect gate="G$1" pin="A4" pad="16"/>
<connect gate="G$1" pin="A5" pad="15"/>
<connect gate="G$1" pin="A6" pad="14"/>
<connect gate="G$1" pin="A7" pad="13"/>
<connect gate="G$1" pin="A8" pad="3"/>
<connect gate="G$1" pin="A9" pad="2"/>
<connect gate="G$1" pin="O0" pad="21"/>
<connect gate="G$1" pin="O1" pad="22"/>
<connect gate="G$1" pin="O2" pad="23"/>
<connect gate="G$1" pin="O3" pad="25"/>
<connect gate="G$1" pin="O4" pad="26"/>
<connect gate="G$1" pin="O5" pad="27"/>
<connect gate="G$1" pin="O6" pad="28"/>
<connect gate="G$1" pin="O7" pad="29"/>
<connect gate="P" pin="GND" pad="24"/>
<connect gate="P" pin="VCC" pad="8"/>
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
<library name="con-lstb">
<description>&lt;b&gt;Pin Headers&lt;/b&gt;&lt;p&gt;
Naming:&lt;p&gt;
MA = male&lt;p&gt;
# contacts - # rows&lt;p&gt;
W = angled&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="MA10-2">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<wire x1="-12.065" y1="2.54" x2="-10.795" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-10.795" y1="2.54" x2="-10.16" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="1.905" x2="-9.525" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-9.525" y1="2.54" x2="-8.255" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-8.255" y1="2.54" x2="-7.62" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-12.065" y1="2.54" x2="-12.7" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-7.62" y1="1.905" x2="-6.985" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-6.985" y1="2.54" x2="-5.715" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-5.715" y1="2.54" x2="-5.08" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-4.445" y1="2.54" x2="-3.175" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="2.54" x2="-2.54" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="1.905" x2="-1.905" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="2.54" x2="-0.635" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="2.54" x2="0" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-4.445" y1="2.54" x2="-5.08" y2="1.905" width="0.1524" layer="21"/>
<wire x1="0" y1="1.905" x2="0.635" y2="2.54" width="0.1524" layer="21"/>
<wire x1="0.635" y1="2.54" x2="1.905" y2="2.54" width="0.1524" layer="21"/>
<wire x1="1.905" y1="2.54" x2="2.54" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="-1.905" x2="-10.795" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-7.62" y1="-1.905" x2="-8.255" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-8.255" y1="-2.54" x2="-9.525" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-9.525" y1="-2.54" x2="-10.16" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-12.7" y1="1.905" x2="-12.7" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-12.7" y1="-1.905" x2="-12.065" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-10.795" y1="-2.54" x2="-12.065" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="-1.905" x2="-5.715" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-5.715" y1="-2.54" x2="-6.985" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-6.985" y1="-2.54" x2="-7.62" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-1.905" x2="-3.175" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="0" y1="-1.905" x2="-0.635" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="-2.54" x2="-1.905" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="-2.54" x2="-2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="-1.905" x2="-4.445" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="-2.54" x2="-4.445" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-1.905" x2="1.905" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-2.54" x2="0.635" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="0.635" y1="-2.54" x2="0" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="3.175" y1="2.54" x2="4.445" y2="2.54" width="0.1524" layer="21"/>
<wire x1="4.445" y1="2.54" x2="5.08" y2="1.905" width="0.1524" layer="21"/>
<wire x1="5.08" y1="1.905" x2="5.715" y2="2.54" width="0.1524" layer="21"/>
<wire x1="12.065" y1="2.54" x2="12.7" y2="1.905" width="0.1524" layer="21"/>
<wire x1="3.175" y1="2.54" x2="2.54" y2="1.905" width="0.1524" layer="21"/>
<wire x1="12.7" y1="1.905" x2="12.7" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="5.08" y1="-1.905" x2="4.445" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="12.7" y1="-1.905" x2="12.065" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="5.715" y1="-2.54" x2="5.08" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-1.905" x2="3.175" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="4.445" y1="-2.54" x2="3.175" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="5.715" y1="-2.54" x2="6.985" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="7.62" y1="-1.905" x2="6.985" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="7.62" y1="-1.905" x2="8.255" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="8.255" y1="-2.54" x2="9.525" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="10.16" y1="-1.905" x2="9.525" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="10.16" y1="-1.905" x2="10.795" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="10.795" y1="-2.54" x2="12.065" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="5.715" y1="2.54" x2="6.985" y2="2.54" width="0.1524" layer="21"/>
<wire x1="7.62" y1="1.905" x2="6.985" y2="2.54" width="0.1524" layer="21"/>
<wire x1="7.62" y1="1.905" x2="8.255" y2="2.54" width="0.1524" layer="21"/>
<wire x1="8.255" y1="2.54" x2="9.525" y2="2.54" width="0.1524" layer="21"/>
<wire x1="10.16" y1="1.905" x2="9.525" y2="2.54" width="0.1524" layer="21"/>
<wire x1="10.16" y1="1.905" x2="10.795" y2="2.54" width="0.1524" layer="21"/>
<wire x1="10.795" y1="2.54" x2="12.065" y2="2.54" width="0.1524" layer="21"/>
<pad name="1" x="-11.43" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="3" x="-8.89" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="5" x="-6.35" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="7" x="-3.81" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="9" x="-1.27" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="11" x="1.27" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="2" x="-11.43" y="1.27" drill="1.016" shape="octagon"/>
<pad name="4" x="-8.89" y="1.27" drill="1.016" shape="octagon"/>
<pad name="6" x="-6.35" y="1.27" drill="1.016" shape="octagon"/>
<pad name="8" x="-3.81" y="1.27" drill="1.016" shape="octagon"/>
<pad name="10" x="-1.27" y="1.27" drill="1.016" shape="octagon"/>
<pad name="12" x="1.27" y="1.27" drill="1.016" shape="octagon"/>
<pad name="13" x="3.81" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="15" x="6.35" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="14" x="3.81" y="1.27" drill="1.016" shape="octagon"/>
<pad name="16" x="6.35" y="1.27" drill="1.016" shape="octagon"/>
<pad name="17" x="8.89" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="18" x="8.89" y="1.27" drill="1.016" shape="octagon"/>
<pad name="19" x="11.43" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="20" x="11.43" y="1.27" drill="1.016" shape="octagon"/>
<text x="-11.938" y="-4.191" size="1.27" layer="21" ratio="10">1</text>
<text x="-12.7" y="2.921" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="2.54" y="-4.191" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<text x="10.16" y="2.921" size="1.27" layer="21" ratio="10">20</text>
<rectangle x1="-9.144" y1="-1.524" x2="-8.636" y2="-1.016" layer="51"/>
<rectangle x1="-11.684" y1="-1.524" x2="-11.176" y2="-1.016" layer="51"/>
<rectangle x1="-6.604" y1="-1.524" x2="-6.096" y2="-1.016" layer="51"/>
<rectangle x1="-1.524" y1="-1.524" x2="-1.016" y2="-1.016" layer="51"/>
<rectangle x1="-4.064" y1="-1.524" x2="-3.556" y2="-1.016" layer="51"/>
<rectangle x1="1.016" y1="-1.524" x2="1.524" y2="-1.016" layer="51"/>
<rectangle x1="-11.684" y1="1.016" x2="-11.176" y2="1.524" layer="51"/>
<rectangle x1="-9.144" y1="1.016" x2="-8.636" y2="1.524" layer="51"/>
<rectangle x1="-6.604" y1="1.016" x2="-6.096" y2="1.524" layer="51"/>
<rectangle x1="-4.064" y1="1.016" x2="-3.556" y2="1.524" layer="51"/>
<rectangle x1="-1.524" y1="1.016" x2="-1.016" y2="1.524" layer="51"/>
<rectangle x1="1.016" y1="1.016" x2="1.524" y2="1.524" layer="51"/>
<rectangle x1="6.096" y1="-1.524" x2="6.604" y2="-1.016" layer="51"/>
<rectangle x1="3.556" y1="-1.524" x2="4.064" y2="-1.016" layer="51"/>
<rectangle x1="3.556" y1="1.016" x2="4.064" y2="1.524" layer="51"/>
<rectangle x1="6.096" y1="1.016" x2="6.604" y2="1.524" layer="51"/>
<rectangle x1="8.636" y1="1.016" x2="9.144" y2="1.524" layer="51"/>
<rectangle x1="11.176" y1="1.016" x2="11.684" y2="1.524" layer="51"/>
<rectangle x1="8.636" y1="-1.524" x2="9.144" y2="-1.016" layer="51"/>
<rectangle x1="11.176" y1="-1.524" x2="11.684" y2="-1.016" layer="51"/>
</package>
</packages>
<symbols>
<symbol name="MA10-2">
<wire x1="3.81" y1="-12.7" x2="-3.81" y2="-12.7" width="0.4064" layer="94"/>
<wire x1="1.27" y1="-5.08" x2="2.54" y2="-5.08" width="0.6096" layer="94"/>
<wire x1="1.27" y1="-7.62" x2="2.54" y2="-7.62" width="0.6096" layer="94"/>
<wire x1="1.27" y1="-10.16" x2="2.54" y2="-10.16" width="0.6096" layer="94"/>
<wire x1="-2.54" y1="-5.08" x2="-1.27" y2="-5.08" width="0.6096" layer="94"/>
<wire x1="-2.54" y1="-7.62" x2="-1.27" y2="-7.62" width="0.6096" layer="94"/>
<wire x1="-2.54" y1="-10.16" x2="-1.27" y2="-10.16" width="0.6096" layer="94"/>
<wire x1="1.27" y1="0" x2="2.54" y2="0" width="0.6096" layer="94"/>
<wire x1="1.27" y1="-2.54" x2="2.54" y2="-2.54" width="0.6096" layer="94"/>
<wire x1="-2.54" y1="0" x2="-1.27" y2="0" width="0.6096" layer="94"/>
<wire x1="-2.54" y1="-2.54" x2="-1.27" y2="-2.54" width="0.6096" layer="94"/>
<wire x1="1.27" y1="7.62" x2="2.54" y2="7.62" width="0.6096" layer="94"/>
<wire x1="1.27" y1="5.08" x2="2.54" y2="5.08" width="0.6096" layer="94"/>
<wire x1="1.27" y1="2.54" x2="2.54" y2="2.54" width="0.6096" layer="94"/>
<wire x1="-2.54" y1="7.62" x2="-1.27" y2="7.62" width="0.6096" layer="94"/>
<wire x1="-2.54" y1="5.08" x2="-1.27" y2="5.08" width="0.6096" layer="94"/>
<wire x1="-2.54" y1="2.54" x2="-1.27" y2="2.54" width="0.6096" layer="94"/>
<wire x1="-3.81" y1="15.24" x2="-3.81" y2="-12.7" width="0.4064" layer="94"/>
<wire x1="3.81" y1="-12.7" x2="3.81" y2="15.24" width="0.4064" layer="94"/>
<wire x1="-3.81" y1="15.24" x2="3.81" y2="15.24" width="0.4064" layer="94"/>
<wire x1="1.27" y1="12.7" x2="2.54" y2="12.7" width="0.6096" layer="94"/>
<wire x1="1.27" y1="10.16" x2="2.54" y2="10.16" width="0.6096" layer="94"/>
<wire x1="-2.54" y1="12.7" x2="-1.27" y2="12.7" width="0.6096" layer="94"/>
<wire x1="-2.54" y1="10.16" x2="-1.27" y2="10.16" width="0.6096" layer="94"/>
<text x="-3.81" y="-15.24" size="1.778" layer="96">&gt;VALUE</text>
<text x="-3.81" y="16.002" size="1.778" layer="95">&gt;NAME</text>
<pin name="1" x="7.62" y="-10.16" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="3" x="7.62" y="-7.62" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="5" x="7.62" y="-5.08" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="2" x="-7.62" y="-10.16" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="4" x="-7.62" y="-7.62" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="6" x="-7.62" y="-5.08" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="7" x="7.62" y="-2.54" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="9" x="7.62" y="0" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="8" x="-7.62" y="-2.54" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="10" x="-7.62" y="0" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="11" x="7.62" y="2.54" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="13" x="7.62" y="5.08" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="15" x="7.62" y="7.62" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="12" x="-7.62" y="2.54" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="14" x="-7.62" y="5.08" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="16" x="-7.62" y="7.62" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="17" x="7.62" y="10.16" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="19" x="7.62" y="12.7" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="18" x="-7.62" y="10.16" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="20" x="-7.62" y="12.7" visible="pad" length="middle" direction="pas" swaplevel="1"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="MA10-2" prefix="SV" uservalue="yes">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="MA10-2" x="0" y="0"/>
</gates>
<devices>
<device name="" package="MA10-2">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="10" pad="10"/>
<connect gate="G$1" pin="11" pad="11"/>
<connect gate="G$1" pin="12" pad="12"/>
<connect gate="G$1" pin="13" pad="13"/>
<connect gate="G$1" pin="14" pad="14"/>
<connect gate="G$1" pin="15" pad="15"/>
<connect gate="G$1" pin="16" pad="16"/>
<connect gate="G$1" pin="17" pad="17"/>
<connect gate="G$1" pin="18" pad="18"/>
<connect gate="G$1" pin="19" pad="19"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="20" pad="20"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
<connect gate="G$1" pin="7" pad="7"/>
<connect gate="G$1" pin="8" pad="8"/>
<connect gate="G$1" pin="9" pad="9"/>
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
<part name="SV1" library="con-lstb" deviceset="MA10-2" device=""/>
<part name="SV2" library="con-lstb" deviceset="MA10-2" device=""/>
<part name="IC2" library="atmel" deviceset="27C080" device="32P6"/>
</parts>
<sheets>
<sheet>
<plain>
<wire x1="0" y1="0" x2="203.2" y2="0" width="0.1524" layer="94"/>
<wire x1="203.2" y1="0" x2="279.4" y2="0" width="0.1524" layer="94"/>
<wire x1="279.4" y1="0" x2="279.4" y2="25.4" width="0.1524" layer="94"/>
<wire x1="279.4" y1="25.4" x2="279.4" y2="196.85" width="0.1524" layer="94"/>
<wire x1="279.4" y1="196.85" x2="0" y2="196.85" width="0.1524" layer="94"/>
<wire x1="0" y1="196.85" x2="0" y2="0" width="0.1524" layer="94"/>
<wire x1="203.2" y1="0" x2="203.2" y2="25.4" width="0.1524" layer="94"/>
<wire x1="203.2" y1="25.4" x2="279.4" y2="25.4" width="0.1524" layer="94"/>
<wire x1="0" y1="0" x2="0" y2="-196.85" width="0.1524" layer="94"/>
<wire x1="0" y1="-196.85" x2="203.2" y2="-196.85" width="0.1524" layer="94"/>
<wire x1="203.2" y1="-196.85" x2="279.4" y2="-196.85" width="0.1524" layer="94"/>
<wire x1="279.4" y1="-196.85" x2="279.4" y2="-171.45" width="0.1524" layer="94"/>
<wire x1="279.4" y1="-171.45" x2="279.4" y2="0" width="0.1524" layer="94"/>
<wire x1="203.2" y1="-196.85" x2="203.2" y2="-171.45" width="0.1524" layer="94"/>
<wire x1="203.2" y1="-171.45" x2="279.4" y2="-171.45" width="0.1524" layer="94"/>
<text x="205.486" y="20.066" size="2.54" layer="94">6U Base board</text>
<text x="206.756" y="-176.784" size="2.54" layer="94">6U Base board</text>
<text x="207.01" y="-180.34" size="1.778" layer="94">for ATMEGA16,AT90S8535</text>
<text x="207.01" y="-185.166" size="1.778" layer="94">case: U-KM19</text>
</plain>
<instances>
<instance part="SV1" gate="G$1" x="228.6" y="-53.34"/>
<instance part="SV2" gate="G$1" x="228.6" y="-124.46"/>
<instance part="IC2" gate="G$1" x="137.16" y="-101.6"/>
</instances>
<busses>
</busses>
<nets>
<net name="GND" class="0">
<segment>
<pinref part="SV1" gate="G$1" pin="2"/>
<wire x1="220.98" y1="-63.5" x2="205.74" y2="-63.5" width="0.1524" layer="91"/>
<label x="208.28" y="-63.5" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="SV2" gate="G$1" pin="2"/>
<wire x1="220.98" y1="-134.62" x2="205.74" y2="-134.62" width="0.1524" layer="91"/>
<label x="210.82" y="-134.62" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="SV1" gate="G$1" pin="1"/>
<wire x1="236.22" y1="-63.5" x2="251.46" y2="-63.5" width="0.1524" layer="91"/>
<label x="241.3" y="-63.5" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="SV2" gate="G$1" pin="1"/>
<wire x1="236.22" y1="-134.62" x2="251.46" y2="-134.62" width="0.1524" layer="91"/>
<label x="241.3" y="-134.62" size="1.778" layer="95"/>
</segment>
</net>
<net name="VCC" class="0">
<segment>
<pinref part="SV1" gate="G$1" pin="20"/>
<wire x1="220.98" y1="-40.64" x2="205.74" y2="-40.64" width="0.1524" layer="91"/>
<label x="208.28" y="-40.64" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="SV2" gate="G$1" pin="20"/>
<wire x1="220.98" y1="-111.76" x2="205.74" y2="-111.76" width="0.1524" layer="91"/>
<label x="210.82" y="-111.76" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="SV1" gate="G$1" pin="19"/>
<wire x1="236.22" y1="-40.64" x2="251.46" y2="-40.64" width="0.1524" layer="91"/>
<label x="241.3" y="-40.64" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="SV2" gate="G$1" pin="19"/>
<wire x1="236.22" y1="-111.76" x2="251.46" y2="-111.76" width="0.1524" layer="91"/>
<label x="241.3" y="-111.76" size="1.778" layer="95"/>
</segment>
</net>
<net name="PC7" class="0">
<segment>
<pinref part="SV1" gate="G$1" pin="18"/>
<wire x1="220.98" y1="-43.18" x2="205.74" y2="-43.18" width="0.1524" layer="91"/>
<label x="208.28" y="-43.18" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC2" gate="G$1" pin="A15"/>
<wire x1="127" y1="-111.76" x2="111.76" y2="-111.76" width="0.1524" layer="91"/>
<label x="114.3" y="-111.76" size="1.778" layer="95"/>
</segment>
</net>
<net name="PC6" class="0">
<segment>
<pinref part="SV1" gate="G$1" pin="16"/>
<wire x1="220.98" y1="-45.72" x2="205.74" y2="-45.72" width="0.1524" layer="91"/>
<label x="208.28" y="-45.72" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC2" gate="G$1" pin="A14"/>
<wire x1="127" y1="-109.22" x2="111.76" y2="-109.22" width="0.1524" layer="91"/>
<label x="114.3" y="-109.22" size="1.778" layer="95"/>
</segment>
</net>
<net name="PC5" class="0">
<segment>
<pinref part="SV1" gate="G$1" pin="14"/>
<wire x1="220.98" y1="-48.26" x2="205.74" y2="-48.26" width="0.1524" layer="91"/>
<label x="208.28" y="-48.26" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC2" gate="G$1" pin="A13"/>
<wire x1="127" y1="-106.68" x2="111.76" y2="-106.68" width="0.1524" layer="91"/>
<label x="114.3" y="-106.68" size="1.778" layer="95"/>
</segment>
</net>
<net name="PC4" class="0">
<segment>
<pinref part="SV1" gate="G$1" pin="12"/>
<wire x1="220.98" y1="-50.8" x2="205.74" y2="-50.8" width="0.1524" layer="91"/>
<label x="208.28" y="-50.8" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC2" gate="G$1" pin="A12"/>
<wire x1="127" y1="-104.14" x2="111.76" y2="-104.14" width="0.1524" layer="91"/>
<label x="114.3" y="-104.14" size="1.778" layer="95"/>
</segment>
</net>
<net name="PC3" class="0">
<segment>
<pinref part="SV1" gate="G$1" pin="10"/>
<wire x1="220.98" y1="-53.34" x2="205.74" y2="-53.34" width="0.1524" layer="91"/>
<label x="208.28" y="-53.34" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC2" gate="G$1" pin="A11"/>
<wire x1="127" y1="-101.6" x2="111.76" y2="-101.6" width="0.1524" layer="91"/>
<label x="114.3" y="-101.6" size="1.778" layer="95"/>
</segment>
</net>
<net name="PC2" class="0">
<segment>
<pinref part="SV1" gate="G$1" pin="8"/>
<wire x1="220.98" y1="-55.88" x2="205.74" y2="-55.88" width="0.1524" layer="91"/>
<label x="208.28" y="-55.88" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC2" gate="G$1" pin="A10"/>
<wire x1="127" y1="-99.06" x2="111.76" y2="-99.06" width="0.1524" layer="91"/>
<label x="114.3" y="-99.06" size="1.778" layer="95"/>
</segment>
</net>
<net name="PC1" class="0">
<segment>
<pinref part="SV1" gate="G$1" pin="6"/>
<wire x1="220.98" y1="-58.42" x2="205.74" y2="-58.42" width="0.1524" layer="91"/>
<label x="208.28" y="-58.42" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC2" gate="G$1" pin="A9"/>
<wire x1="127" y1="-96.52" x2="111.76" y2="-96.52" width="0.1524" layer="91"/>
<label x="114.3" y="-96.52" size="1.778" layer="95"/>
</segment>
</net>
<net name="PC0" class="0">
<segment>
<pinref part="SV1" gate="G$1" pin="4"/>
<wire x1="220.98" y1="-60.96" x2="205.74" y2="-60.96" width="0.1524" layer="91"/>
<label x="208.28" y="-60.96" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC2" gate="G$1" pin="A8"/>
<wire x1="127" y1="-93.98" x2="111.76" y2="-93.98" width="0.1524" layer="91"/>
<label x="114.3" y="-93.98" size="1.778" layer="95"/>
</segment>
</net>
<net name="PB7" class="0">
<segment>
<pinref part="SV2" gate="G$1" pin="17"/>
<wire x1="236.22" y1="-114.3" x2="251.46" y2="-114.3" width="0.1524" layer="91"/>
<label x="241.3" y="-114.3" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC2" gate="G$1" pin="A7"/>
<wire x1="127" y1="-91.44" x2="111.76" y2="-91.44" width="0.1524" layer="91"/>
<label x="114.3" y="-91.44" size="1.778" layer="95"/>
</segment>
</net>
<net name="PB6" class="0">
<segment>
<pinref part="SV2" gate="G$1" pin="15"/>
<wire x1="236.22" y1="-116.84" x2="251.46" y2="-116.84" width="0.1524" layer="91"/>
<label x="241.3" y="-116.84" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC2" gate="G$1" pin="A6"/>
<wire x1="127" y1="-88.9" x2="111.76" y2="-88.9" width="0.1524" layer="91"/>
<label x="114.3" y="-88.9" size="1.778" layer="95"/>
</segment>
</net>
<net name="PB5" class="0">
<segment>
<pinref part="SV2" gate="G$1" pin="13"/>
<wire x1="236.22" y1="-119.38" x2="251.46" y2="-119.38" width="0.1524" layer="91"/>
<label x="241.3" y="-119.38" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC2" gate="G$1" pin="A5"/>
<wire x1="127" y1="-86.36" x2="111.76" y2="-86.36" width="0.1524" layer="91"/>
<label x="114.3" y="-86.36" size="1.778" layer="95"/>
</segment>
</net>
<net name="PB4" class="0">
<segment>
<pinref part="SV2" gate="G$1" pin="11"/>
<wire x1="236.22" y1="-121.92" x2="251.46" y2="-121.92" width="0.1524" layer="91"/>
<label x="241.3" y="-121.92" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC2" gate="G$1" pin="A4"/>
<wire x1="127" y1="-83.82" x2="111.76" y2="-83.82" width="0.1524" layer="91"/>
<label x="114.3" y="-83.82" size="1.778" layer="95"/>
</segment>
</net>
<net name="PB3" class="0">
<segment>
<pinref part="SV2" gate="G$1" pin="9"/>
<wire x1="236.22" y1="-124.46" x2="251.46" y2="-124.46" width="0.1524" layer="91"/>
<label x="241.3" y="-124.46" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC2" gate="G$1" pin="A3"/>
<wire x1="127" y1="-81.28" x2="111.76" y2="-81.28" width="0.1524" layer="91"/>
<label x="114.3" y="-81.28" size="1.778" layer="95"/>
</segment>
</net>
<net name="PB2" class="0">
<segment>
<pinref part="SV2" gate="G$1" pin="7"/>
<wire x1="236.22" y1="-127" x2="251.46" y2="-127" width="0.1524" layer="91"/>
<label x="241.3" y="-127" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC2" gate="G$1" pin="A2"/>
<wire x1="127" y1="-78.74" x2="111.76" y2="-78.74" width="0.1524" layer="91"/>
<label x="114.3" y="-78.74" size="1.778" layer="95"/>
</segment>
</net>
<net name="PB1" class="0">
<segment>
<pinref part="SV2" gate="G$1" pin="5"/>
<wire x1="236.22" y1="-129.54" x2="251.46" y2="-129.54" width="0.1524" layer="91"/>
<label x="241.3" y="-129.54" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC2" gate="G$1" pin="A1"/>
<wire x1="127" y1="-76.2" x2="111.76" y2="-76.2" width="0.1524" layer="91"/>
<label x="114.3" y="-76.2" size="1.778" layer="95"/>
</segment>
</net>
<net name="PB0" class="0">
<segment>
<pinref part="SV2" gate="G$1" pin="3"/>
<wire x1="236.22" y1="-132.08" x2="251.46" y2="-132.08" width="0.1524" layer="91"/>
<label x="241.3" y="-132.08" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC2" gate="G$1" pin="A0"/>
<wire x1="127" y1="-73.66" x2="111.76" y2="-73.66" width="0.1524" layer="91"/>
<label x="114.3" y="-73.66" size="1.778" layer="95"/>
</segment>
</net>
<net name="PD7" class="0">
<segment>
<pinref part="SV1" gate="G$1" pin="17"/>
<wire x1="236.22" y1="-43.18" x2="251.46" y2="-43.18" width="0.1524" layer="91"/>
<label x="241.3" y="-43.18" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC2" gate="G$1" pin="A19"/>
<wire x1="127" y1="-121.92" x2="111.76" y2="-121.92" width="0.1524" layer="91"/>
<label x="114.3" y="-121.92" size="1.778" layer="95"/>
</segment>
</net>
<net name="PD6" class="0">
<segment>
<pinref part="SV1" gate="G$1" pin="15"/>
<wire x1="236.22" y1="-45.72" x2="251.46" y2="-45.72" width="0.1524" layer="91"/>
<label x="241.3" y="-45.72" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC2" gate="G$1" pin="A18"/>
<wire x1="127" y1="-119.38" x2="111.76" y2="-119.38" width="0.1524" layer="91"/>
<label x="114.3" y="-119.38" size="1.778" layer="95"/>
</segment>
</net>
<net name="PD5" class="0">
<segment>
<pinref part="SV1" gate="G$1" pin="13"/>
<wire x1="236.22" y1="-48.26" x2="251.46" y2="-48.26" width="0.1524" layer="91"/>
<label x="241.3" y="-48.26" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC2" gate="G$1" pin="A17"/>
<wire x1="127" y1="-116.84" x2="111.76" y2="-116.84" width="0.1524" layer="91"/>
<label x="114.3" y="-116.84" size="1.778" layer="95"/>
</segment>
</net>
<net name="PD4" class="0">
<segment>
<pinref part="SV1" gate="G$1" pin="11"/>
<wire x1="236.22" y1="-50.8" x2="251.46" y2="-50.8" width="0.1524" layer="91"/>
<label x="241.3" y="-50.8" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC2" gate="G$1" pin="A16"/>
<wire x1="127" y1="-114.3" x2="111.76" y2="-114.3" width="0.1524" layer="91"/>
<label x="114.3" y="-114.3" size="1.778" layer="95"/>
</segment>
</net>
<net name="PD3" class="0">
<segment>
<pinref part="SV1" gate="G$1" pin="9"/>
<wire x1="236.22" y1="-53.34" x2="251.46" y2="-53.34" width="0.1524" layer="91"/>
<label x="241.3" y="-53.34" size="1.778" layer="95"/>
</segment>
</net>
<net name="PD2" class="0">
<segment>
<pinref part="SV1" gate="G$1" pin="7"/>
<wire x1="236.22" y1="-55.88" x2="251.46" y2="-55.88" width="0.1524" layer="91"/>
<label x="241.3" y="-55.88" size="1.778" layer="95"/>
</segment>
</net>
<net name="PD1" class="0">
<segment>
<pinref part="SV1" gate="G$1" pin="5"/>
<wire x1="236.22" y1="-58.42" x2="251.46" y2="-58.42" width="0.1524" layer="91"/>
<label x="241.3" y="-58.42" size="1.778" layer="95"/>
</segment>
</net>
<net name="PD0" class="0">
<segment>
<pinref part="SV1" gate="G$1" pin="3"/>
<wire x1="236.22" y1="-60.96" x2="251.46" y2="-60.96" width="0.1524" layer="91"/>
<label x="241.3" y="-60.96" size="1.778" layer="95"/>
</segment>
</net>
<net name="PA7" class="0">
<segment>
<pinref part="SV2" gate="G$1" pin="18"/>
<wire x1="220.98" y1="-114.3" x2="205.74" y2="-114.3" width="0.1524" layer="91"/>
<label x="210.82" y="-114.3" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC2" gate="G$1" pin="O7"/>
<wire x1="147.32" y1="-91.44" x2="162.56" y2="-91.44" width="0.1524" layer="91"/>
<label x="152.4" y="-91.44" size="1.778" layer="95"/>
</segment>
</net>
<net name="PA6" class="0">
<segment>
<pinref part="SV2" gate="G$1" pin="16"/>
<wire x1="220.98" y1="-116.84" x2="205.74" y2="-116.84" width="0.1524" layer="91"/>
<label x="210.82" y="-116.84" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC2" gate="G$1" pin="O6"/>
<wire x1="147.32" y1="-88.9" x2="162.56" y2="-88.9" width="0.1524" layer="91"/>
<label x="152.4" y="-88.9" size="1.778" layer="95"/>
</segment>
</net>
<net name="PA5" class="0">
<segment>
<pinref part="SV2" gate="G$1" pin="14"/>
<wire x1="220.98" y1="-119.38" x2="205.74" y2="-119.38" width="0.1524" layer="91"/>
<label x="210.82" y="-119.38" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC2" gate="G$1" pin="O5"/>
<wire x1="147.32" y1="-86.36" x2="162.56" y2="-86.36" width="0.1524" layer="91"/>
<label x="152.4" y="-86.36" size="1.778" layer="95"/>
</segment>
</net>
<net name="PA4" class="0">
<segment>
<pinref part="SV2" gate="G$1" pin="12"/>
<wire x1="220.98" y1="-121.92" x2="205.74" y2="-121.92" width="0.1524" layer="91"/>
<label x="210.82" y="-121.92" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC2" gate="G$1" pin="O4"/>
<wire x1="147.32" y1="-83.82" x2="162.56" y2="-83.82" width="0.1524" layer="91"/>
<label x="152.4" y="-83.82" size="1.778" layer="95"/>
</segment>
</net>
<net name="PA3" class="0">
<segment>
<pinref part="SV2" gate="G$1" pin="10"/>
<wire x1="220.98" y1="-124.46" x2="205.74" y2="-124.46" width="0.1524" layer="91"/>
<label x="210.82" y="-124.46" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC2" gate="G$1" pin="O3"/>
<wire x1="147.32" y1="-81.28" x2="162.56" y2="-81.28" width="0.1524" layer="91"/>
<label x="152.4" y="-81.28" size="1.778" layer="95"/>
</segment>
</net>
<net name="PA2" class="0">
<segment>
<pinref part="SV2" gate="G$1" pin="8"/>
<wire x1="220.98" y1="-127" x2="205.74" y2="-127" width="0.1524" layer="91"/>
<label x="210.82" y="-127" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC2" gate="G$1" pin="O2"/>
<wire x1="147.32" y1="-78.74" x2="162.56" y2="-78.74" width="0.1524" layer="91"/>
<label x="152.4" y="-78.74" size="1.778" layer="95"/>
</segment>
</net>
<net name="PA1" class="0">
<segment>
<pinref part="SV2" gate="G$1" pin="6"/>
<wire x1="220.98" y1="-129.54" x2="205.74" y2="-129.54" width="0.1524" layer="91"/>
<label x="210.82" y="-129.54" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC2" gate="G$1" pin="O1"/>
<wire x1="147.32" y1="-76.2" x2="162.56" y2="-76.2" width="0.1524" layer="91"/>
<label x="152.4" y="-76.2" size="1.778" layer="95"/>
</segment>
</net>
<net name="PA0" class="0">
<segment>
<pinref part="SV2" gate="G$1" pin="4"/>
<wire x1="220.98" y1="-132.08" x2="205.74" y2="-132.08" width="0.1524" layer="91"/>
<label x="210.82" y="-132.08" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC2" gate="G$1" pin="O0"/>
<wire x1="147.32" y1="-73.66" x2="162.56" y2="-73.66" width="0.1524" layer="91"/>
<label x="152.4" y="-73.66" size="1.778" layer="95"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
