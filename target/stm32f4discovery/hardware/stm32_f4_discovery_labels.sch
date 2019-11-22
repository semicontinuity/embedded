<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="7.7.0">
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
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
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
</parts>
<sheets>
<sheet>
<plain>
<text x="22.86" y="60.96" size="1.778" layer="91">GND</text>
<text x="22.86" y="58.42" size="1.778" layer="91">VDD</text>
<text x="22.86" y="55.88" size="1.778" layer="91">GND</text>
<text x="22.86" y="53.34" size="1.778" layer="91">PC1</text>
<text x="22.86" y="50.8" size="1.778" layer="91">PC3</text>
<text x="22.86" y="48.26" size="1.778" layer="91">PA1</text>
<text x="22.86" y="45.72" size="1.778" layer="91">PA3</text>
<text x="22.86" y="43.18" size="1.778" layer="91">PA5</text>
<text x="22.86" y="40.64" size="1.778" layer="91">PA7</text>
<text x="22.86" y="38.1" size="1.778" layer="91">PC5</text>
<text x="22.86" y="35.56" size="1.778" layer="91">PB1</text>
<text x="22.86" y="33.02" size="1.778" layer="91">GND</text>
<text x="22.86" y="30.48" size="1.778" layer="91">PE7</text>
<text x="22.86" y="27.94" size="1.778" layer="91">PE9</text>
<text x="22.86" y="25.4" size="1.778" layer="91">PE11</text>
<text x="22.86" y="22.86" size="1.778" layer="91">PE13</text>
<text x="22.86" y="20.32" size="1.778" layer="91">PE15</text>
<text x="22.86" y="17.78" size="1.778" layer="91">PB11</text>
<text x="22.86" y="15.24" size="1.778" layer="91">PB13</text>
<text x="22.86" y="12.7" size="1.778" layer="91">PB15</text>
<text x="22.86" y="10.16" size="1.778" layer="91">PD9</text>
<text x="22.86" y="7.62" size="1.778" layer="91">PD11</text>
<text x="22.86" y="5.08" size="1.778" layer="91">PD13</text>
<text x="22.86" y="2.54" size="1.778" layer="91">PD15</text>
<text x="22.86" y="0" size="1.778" layer="91">GND</text>
<text x="38.1" y="0" size="1.778" layer="91">GND</text>
<text x="38.1" y="2.54" size="1.778" layer="91">NC</text>
<text x="38.1" y="5.08" size="1.778" layer="91">PD14</text>
<text x="38.1" y="7.62" size="1.778" layer="91">PD12</text>
<text x="38.1" y="10.16" size="1.778" layer="91">PD10</text>
<text x="38.1" y="12.7" size="1.778" layer="91">PD8</text>
<text x="38.1" y="15.24" size="1.778" layer="91">PB14</text>
<text x="38.1" y="17.78" size="1.778" layer="91">PB12</text>
<text x="38.1" y="20.32" size="1.778" layer="91">PB10</text>
<text x="38.1" y="22.86" size="1.778" layer="91">PE14</text>
<text x="38.1" y="25.4" size="1.778" layer="91">PE12</text>
<text x="38.1" y="27.94" size="1.778" layer="91">PE10</text>
<text x="38.1" y="30.48" size="1.778" layer="91">PE8</text>
<text x="38.1" y="33.02" size="1.778" layer="91">PB2</text>
<text x="38.1" y="35.56" size="1.778" layer="91">PB0</text>
<text x="38.1" y="38.1" size="1.778" layer="91">PC4</text>
<text x="38.1" y="40.64" size="1.778" layer="91">PA6</text>
<text x="38.1" y="43.18" size="1.778" layer="91">PA4</text>
<text x="38.1" y="43.18" size="1.778" layer="91">PA4</text>
<text x="38.1" y="45.72" size="1.778" layer="91">PA2</text>
<text x="38.1" y="48.26" size="1.778" layer="91">PA0</text>
<text x="38.1" y="50.8" size="1.778" layer="91">PC2</text>
<text x="38.1" y="53.34" size="1.778" layer="91">PC0</text>
<text x="38.1" y="55.88" size="1.778" layer="91">NRST</text>
<text x="38.1" y="58.42" size="1.778" layer="91">VDD</text>
<text x="38.1" y="60.96" size="1.778" layer="91">GND</text>
<text x="53.34" y="0" size="1.778" layer="91">GND</text>
<text x="53.34" y="2.54" size="1.778" layer="91">PC6</text>
<text x="53.34" y="5.08" size="1.778" layer="91">PC8</text>
<text x="53.34" y="7.62" size="1.778" layer="91">PA8</text>
<text x="53.34" y="10.16" size="1.778" layer="91">PA10</text>
<text x="53.34" y="12.7" size="1.778" layer="91">PA14</text>
<text x="53.34" y="15.24" size="1.778" layer="91">PC10</text>
<text x="53.34" y="17.78" size="1.778" layer="91">PC12</text>
<text x="53.34" y="20.32" size="1.778" layer="91">PD1</text>
<text x="53.34" y="22.86" size="1.778" layer="91">PD3</text>
<text x="53.34" y="25.4" size="1.778" layer="91">PD5</text>
<text x="53.34" y="27.94" size="1.778" layer="91">PD7</text>
<text x="53.34" y="30.48" size="1.778" layer="91">PB4</text>
<text x="53.34" y="33.02" size="1.778" layer="91">PB6</text>
<text x="53.34" y="35.56" size="1.778" layer="91">BOOT0</text>
<text x="53.34" y="38.1" size="1.778" layer="91">PB8</text>
<text x="53.34" y="40.64" size="1.778" layer="91">PE0</text>
<text x="53.34" y="43.18" size="1.778" layer="91">PE2</text>
<text x="53.34" y="45.72" size="1.778" layer="91">PE4</text>
<text x="53.34" y="48.26" size="1.778" layer="91">PE6</text>
<text x="53.34" y="50.8" size="1.778" layer="91">PC14</text>
<text x="53.34" y="53.34" size="1.778" layer="91">PH0</text>
<text x="53.34" y="55.88" size="1.778" layer="91">3V</text>
<text x="53.34" y="58.42" size="1.778" layer="91">5V</text>
<text x="53.34" y="60.96" size="1.778" layer="91">GND</text>
<text x="68.58" y="60.96" size="1.778" layer="91">GND</text>
<text x="68.58" y="58.42" size="1.778" layer="91">5V</text>
<text x="68.58" y="55.88" size="1.778" layer="91">3V</text>
<text x="68.58" y="53.34" size="1.778" layer="91">PH1</text>
<text x="68.58" y="50.8" size="1.778" layer="91">PC15</text>
<text x="68.58" y="48.26" size="1.778" layer="91">PC13</text>
<text x="68.58" y="45.72" size="1.778" layer="91">PE5</text>
<text x="68.58" y="43.18" size="1.778" layer="91">PE3</text>
<text x="68.58" y="40.64" size="1.778" layer="91">PE1</text>
<text x="68.58" y="38.1" size="1.778" layer="91">PB9</text>
<text x="68.58" y="35.56" size="1.778" layer="91">VDD</text>
<text x="68.58" y="33.02" size="1.778" layer="91">PB7</text>
<text x="68.58" y="30.48" size="1.778" layer="91">PB5</text>
<text x="68.58" y="27.94" size="1.778" layer="91">PB3</text>
<text x="68.58" y="25.4" size="1.778" layer="91">PD6</text>
<text x="68.58" y="22.86" size="1.778" layer="91">PD4</text>
<text x="68.58" y="20.32" size="1.778" layer="91">PD2</text>
<text x="68.58" y="17.78" size="1.778" layer="91">PD0</text>
<text x="68.58" y="15.24" size="1.778" layer="91">PC11</text>
<text x="68.58" y="12.7" size="1.778" layer="91">PA15</text>
<text x="68.58" y="10.16" size="1.778" layer="91">PA13</text>
<text x="68.58" y="7.62" size="1.778" layer="91">PA9</text>
<text x="68.58" y="5.08" size="1.778" layer="91">PC9</text>
<text x="68.58" y="2.54" size="1.778" layer="91">PC7</text>
<text x="68.58" y="0" size="1.778" layer="91">GND</text>
</plain>
<instances>
</instances>
<busses>
</busses>
<nets>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
