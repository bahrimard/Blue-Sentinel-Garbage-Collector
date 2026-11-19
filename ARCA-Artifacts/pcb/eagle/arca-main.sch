<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="9.6.2">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.635" unitdist="mm" unit="mm" style="lines" multiple="1" display="no" altdistance="0.127" altunitdist="mm" altunit="mm"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="yes" active="yes"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="yes" active="yes"/>
<layer number="17" name="Pads" color="2" fill="1" visible="yes" active="yes"/>
<layer number="18" name="Vias" color="2" fill="1" visible="yes" active="yes"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="yes" active="yes"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="yes" active="yes"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="yes" active="yes"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="yes" active="yes"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="yes" active="yes"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="yes" active="yes"/>
<layer number="25" name="tNames" color="7" fill="1" visible="yes" active="yes"/>
<layer number="26" name="bNames" color="7" fill="1" visible="yes" active="yes"/>
<layer number="27" name="tValues" color="7" fill="1" visible="yes" active="yes"/>
<layer number="28" name="bValues" color="7" fill="1" visible="yes" active="yes"/>
<layer number="29" name="tStop" color="7" fill="1" visible="yes" active="yes"/>
<layer number="30" name="bStop" color="7" fill="1" visible="yes" active="yes"/>
<layer number="31" name="tCream" color="7" fill="1" visible="yes" active="yes"/>
<layer number="32" name="bCream" color="7" fill="1" visible="yes" active="yes"/>
<layer number="35" name="tGlue" color="7" fill="1" visible="yes" active="yes"/>
<layer number="36" name="bGlue" color="7" fill="1" visible="yes" active="yes"/>
<layer number="39" name="tKeepout" color="4" fill="1" visible="yes" active="yes"/>
<layer number="40" name="bKeepout" color="1" fill="1" visible="yes" active="yes"/>
<layer number="41" name="tRestrict" color="4" fill="1" visible="yes" active="yes"/>
<layer number="42" name="bRestrict" color="1" fill="1" visible="yes" active="yes"/>
<layer number="43" name="vRestrict" color="2" fill="1" visible="yes" active="yes"/>
<layer number="44" name="Drills" color="7" fill="1" visible="yes" active="yes"/>
<layer number="45" name="Holes" color="7" fill="1" visible="yes" active="yes"/>
<layer number="46" name="Milling" color="3" fill="1" visible="yes" active="yes"/>
<layer number="47" name="Measures" color="7" fill="1" visible="yes" active="yes"/>
<layer number="48" name="Document" color="7" fill="1" visible="yes" active="yes"/>
<layer number="49" name="Reference" color="7" fill="1" visible="yes" active="yes"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="yes" active="yes"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="yes" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="arca">
<description>ARCA IoT River Cleaning Boat — part library</description>
<packages>
<package name="CAP_RAD_2.54">
<description>Kapasitor radial pitch 2.54, pad 1 = +</description>
<pad name="1" x="-1.27" y="0" drill="0.9" diameter="1.7" shape="square"/>
<pad name="2" x="1.27" y="0" drill="0.9" diameter="1.7" shape="round"/>
<wire x1="-2.4" y1="1.6" x2="-1.6" y2="1.6" width="0.2" layer="21"/>
<wire x1="-2" y1="2" x2="-2" y2="1.2" width="0.2" layer="21"/>
<circle x="0" y="0" radius="2.5" width="0.2" layer="21"/>
<text x="0" y="2.2" size="1.016" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-2.2" size="1.016" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="ESP32_DEVKIT_V1_30">
<description>ESP32 DOIT DevKit V1 30 pin, socket 2x15, jarak baris 25.4 mm</description>
<pad name="L1" x="-12.7" y="17.78" drill="1" diameter="1.8" shape="square"/>
<pad name="R1" x="12.7" y="17.78" drill="1" diameter="1.8" shape="round"/>
<pad name="L2" x="-12.7" y="15.24" drill="1" diameter="1.8" shape="round"/>
<pad name="R2" x="12.7" y="15.24" drill="1" diameter="1.8" shape="round"/>
<pad name="L3" x="-12.7" y="12.7" drill="1" diameter="1.8" shape="round"/>
<pad name="R3" x="12.7" y="12.7" drill="1" diameter="1.8" shape="round"/>
<pad name="L4" x="-12.7" y="10.16" drill="1" diameter="1.8" shape="round"/>
<pad name="R4" x="12.7" y="10.16" drill="1" diameter="1.8" shape="round"/>
<pad name="L5" x="-12.7" y="7.62" drill="1" diameter="1.8" shape="round"/>
<pad name="R5" x="12.7" y="7.62" drill="1" diameter="1.8" shape="round"/>
<pad name="L6" x="-12.7" y="5.08" drill="1" diameter="1.8" shape="round"/>
<pad name="R6" x="12.7" y="5.08" drill="1" diameter="1.8" shape="round"/>
<pad name="L7" x="-12.7" y="2.54" drill="1" diameter="1.8" shape="round"/>
<pad name="R7" x="12.7" y="2.54" drill="1" diameter="1.8" shape="round"/>
<pad name="L8" x="-12.7" y="0" drill="1" diameter="1.8" shape="round"/>
<pad name="R8" x="12.7" y="0" drill="1" diameter="1.8" shape="round"/>
<pad name="L9" x="-12.7" y="-2.54" drill="1" diameter="1.8" shape="round"/>
<pad name="R9" x="12.7" y="-2.54" drill="1" diameter="1.8" shape="round"/>
<pad name="L10" x="-12.7" y="-5.08" drill="1" diameter="1.8" shape="round"/>
<pad name="R10" x="12.7" y="-5.08" drill="1" diameter="1.8" shape="round"/>
<pad name="L11" x="-12.7" y="-7.62" drill="1" diameter="1.8" shape="round"/>
<pad name="R11" x="12.7" y="-7.62" drill="1" diameter="1.8" shape="round"/>
<pad name="L12" x="-12.7" y="-10.16" drill="1" diameter="1.8" shape="round"/>
<pad name="R12" x="12.7" y="-10.16" drill="1" diameter="1.8" shape="round"/>
<pad name="L13" x="-12.7" y="-12.7" drill="1" diameter="1.8" shape="round"/>
<pad name="R13" x="12.7" y="-12.7" drill="1" diameter="1.8" shape="round"/>
<pad name="L14" x="-12.7" y="-15.24" drill="1" diameter="1.8" shape="round"/>
<pad name="R14" x="12.7" y="-15.24" drill="1" diameter="1.8" shape="round"/>
<pad name="L15" x="-12.7" y="-17.78" drill="1" diameter="1.8" shape="round"/>
<pad name="R15" x="12.7" y="-17.78" drill="1" diameter="1.8" shape="round"/>
<wire x1="-14.1" y1="-21.3" x2="14.1" y2="-21.3" width="0.2" layer="21"/>
<wire x1="14.1" y1="-21.3" x2="14.1" y2="30.2" width="0.2" layer="21"/>
<wire x1="14.1" y1="30.2" x2="-14.1" y2="30.2" width="0.2" layer="21"/>
<wire x1="-14.1" y1="30.2" x2="-14.1" y2="-21.3" width="0.2" layer="21"/>
<wire x1="-14.1" y1="22" x2="14.1" y2="22" width="0.2" layer="21"/>
<wire x1="-4" y1="-21.3" x2="-4" y2="-24.3" width="0.2" layer="21"/>
<wire x1="-4" y1="-24.3" x2="4" y2="-24.3" width="0.2" layer="21"/>
<wire x1="4" y1="-24.3" x2="4" y2="-21.3" width="0.2" layer="21"/>
<text x="0" y="19.98" size="1.016" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-19.98" size="1.016" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="HDR1X2_BZ">
<description>Header 1x2 ke buzzer aktif 5V (pad 1 = +)</description>
<pad name="1" x="1.27" y="0" drill="1" diameter="1.7" shape="square"/>
<pad name="2" x="-1.27" y="0" drill="1" diameter="1.7" shape="round"/>
<wire x1="-2.54" y1="1.27" x2="2.54" y2="1.27" width="0.2" layer="21"/>
<wire x1="2.54" y1="1.27" x2="2.54" y2="-1.27" width="0.2" layer="21"/>
<wire x1="2.54" y1="-1.27" x2="-2.54" y2="-1.27" width="0.2" layer="21"/>
<wire x1="-2.54" y1="-1.27" x2="-2.54" y2="1.27" width="0.2" layer="21"/>
<text x="0" y="-2.2" size="1.016" layer="25" align="top-center">&gt;NAME</text>
<text x="0" y="-2.2" size="1.016" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="HDR1X4_H">
<description></description>
<pad name="1" x="-3.81" y="0" drill="1" diameter="1.7" shape="square"/>
<pad name="2" x="-1.27" y="0" drill="1" diameter="1.7" shape="round"/>
<pad name="3" x="1.27" y="0" drill="1" diameter="1.7" shape="round"/>
<pad name="4" x="3.81" y="0" drill="1" diameter="1.7" shape="round"/>
<wire x1="-5.08" y1="1.27" x2="5.08" y2="1.27" width="0.2" layer="21"/>
<wire x1="5.08" y1="1.27" x2="5.08" y2="-1.27" width="0.2" layer="21"/>
<wire x1="5.08" y1="-1.27" x2="-5.08" y2="-1.27" width="0.2" layer="21"/>
<wire x1="-5.08" y1="-1.27" x2="-5.08" y2="1.27" width="0.2" layer="21"/>
<text x="-5.8" y="0" size="1.016" layer="25" align="center-right">&gt;NAME</text>
<text x="0" y="-2.2" size="1.016" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="HDR1X6_V">
<description></description>
<pad name="1" x="0" y="6.35" drill="1" diameter="1.7" shape="square"/>
<pad name="2" x="0" y="3.81" drill="1" diameter="1.7" shape="round"/>
<pad name="3" x="0" y="1.27" drill="1" diameter="1.7" shape="round"/>
<pad name="4" x="0" y="-1.27" drill="1" diameter="1.7" shape="round"/>
<pad name="5" x="0" y="-3.81" drill="1" diameter="1.7" shape="round"/>
<pad name="6" x="0" y="-6.35" drill="1" diameter="1.7" shape="round"/>
<wire x1="-1.27" y1="7.62" x2="1.27" y2="7.62" width="0.2" layer="21"/>
<wire x1="1.27" y1="7.62" x2="1.27" y2="-7.62" width="0.2" layer="21"/>
<wire x1="1.27" y1="-7.62" x2="-1.27" y2="-7.62" width="0.2" layer="21"/>
<wire x1="-1.27" y1="-7.62" x2="-1.27" y2="7.62" width="0.2" layer="21"/>
<text x="0" y="8.55" size="1.016" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-8.55" size="1.016" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="JUMPER_WIRE">
<description>Jumper kabel di sisi komponen (pad 1 &amp; 2 satu net)</description>
<pad name="1" x="0" y="0" drill="0.9" diameter="1.8" shape="round"/>
<pad name="2" x="11.9" y="0" drill="0.9" diameter="1.8" shape="round"/>
<wire x1="1.2" y1="0" x2="10.7" y2="0" width="0.2" layer="21"/>
<text x="1.6" y="0" size="1.016" layer="51" align="center-left">&gt;NAME</text>
<text x="0" y="-2.2" size="1.016" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="RES_AX_10.16">
<description>Resistor 1/4 W tidur, pitch 10.16</description>
<pad name="1" x="-5.08" y="0" drill="0.9" diameter="1.8" shape="round"/>
<pad name="2" x="5.08" y="0" drill="0.9" diameter="1.8" shape="round"/>
<wire x1="-3.2" y1="-1.1" x2="3.2" y2="-1.1" width="0.2" layer="21"/>
<wire x1="3.2" y1="-1.1" x2="3.2" y2="1.1" width="0.2" layer="21"/>
<wire x1="3.2" y1="1.1" x2="-3.2" y2="1.1" width="0.2" layer="21"/>
<wire x1="-3.2" y1="1.1" x2="-3.2" y2="-1.1" width="0.2" layer="21"/>
<wire x1="-4.1" y1="0" x2="-3.2" y2="0" width="0.2" layer="21"/>
<wire x1="3.2" y1="0" x2="4.1" y2="0" width="0.2" layer="21"/>
<text x="0" y="-2.2" size="1.016" layer="25" align="top-center">&gt;NAME</text>
<text x="0" y="-2.2" size="1.016" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="TERM2_508">
<description>Terminal screw 2 pin 5.08 mm, kabel masuk dari sisi -y</description>
<pad name="1" x="-2.54" y="0" drill="1.3" diameter="2.6" shape="square"/>
<pad name="2" x="2.54" y="0" drill="1.3" diameter="2.6" shape="round"/>
<wire x1="-5.08" y1="-4.2" x2="5.08" y2="-4.2" width="0.2" layer="21"/>
<wire x1="5.08" y1="-4.2" x2="5.08" y2="3.4" width="0.2" layer="21"/>
<wire x1="5.08" y1="3.4" x2="-5.08" y2="3.4" width="0.2" layer="21"/>
<wire x1="-5.08" y1="3.4" x2="-5.08" y2="-4.2" width="0.2" layer="21"/>
<wire x1="-5.08" y1="-2.8" x2="5.08" y2="-2.8" width="0.2" layer="21"/>
<text x="0" y="2.2" size="1.016" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-2.2" size="1.016" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="TERM3_508">
<description>Terminal screw 3 pin 5.08 mm, kabel masuk dari sisi -y</description>
<pad name="1" x="-5.08" y="0" drill="1.3" diameter="2.6" shape="square"/>
<pad name="2" x="0" y="0" drill="1.3" diameter="2.6" shape="round"/>
<pad name="3" x="5.08" y="0" drill="1.3" diameter="2.6" shape="round"/>
<wire x1="-7.62" y1="-4.2" x2="7.62" y2="-4.2" width="0.2" layer="21"/>
<wire x1="7.62" y1="-4.2" x2="7.62" y2="3.4" width="0.2" layer="21"/>
<wire x1="7.62" y1="3.4" x2="-7.62" y2="3.4" width="0.2" layer="21"/>
<wire x1="-7.62" y1="3.4" x2="-7.62" y2="-4.2" width="0.2" layer="21"/>
<wire x1="-7.62" y1="-2.8" x2="7.62" y2="-2.8" width="0.2" layer="21"/>
<text x="0" y="2.2" size="1.016" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-2.2" size="1.016" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="TO220V">
<description>TO-220 berdiri, tab/heatsink ke +y. 1=IN 2=GND 3=OUT (L7805)</description>
<pad name="1" x="-2.54" y="0" drill="1.1" diameter="1.9" shape="square"/>
<pad name="2" x="0" y="0" drill="1.1" diameter="1.9" shape="round"/>
<pad name="3" x="2.54" y="0" drill="1.1" diameter="1.9" shape="round"/>
<wire x1="-5.1" y1="-1.4" x2="5.1" y2="-1.4" width="0.2" layer="21"/>
<wire x1="5.1" y1="-1.4" x2="5.1" y2="3.4" width="0.2" layer="21"/>
<wire x1="5.1" y1="3.4" x2="-5.1" y2="3.4" width="0.2" layer="21"/>
<wire x1="-5.1" y1="3.4" x2="-5.1" y2="-1.4" width="0.2" layer="21"/>
<wire x1="-5.1" y1="2.2" x2="5.1" y2="2.2" width="0.2" layer="21"/>
<text x="0" y="2.2" size="1.016" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-2.2" size="1.016" layer="27" align="top-center">&gt;VALUE</text>
</package>
<package name="TO92_INLINE">
<description>TO-92 kaki sejajar. BC337: 1=C 2=B 3=E, sisi datar ke -y</description>
<pad name="1" x="-2.54" y="0" drill="0.8" diameter="1.5" shape="round"/>
<pad name="2" x="0" y="0" drill="0.8" diameter="1.5" shape="round"/>
<pad name="3" x="2.54" y="0" drill="0.8" diameter="1.5" shape="round"/>
<wire x1="-2.4" y1="-1.6" x2="2.4" y2="-1.6" width="0.2" layer="21"/>
<wire x1="-2.4" y1="-1.6" x2="2.4" y2="-1.6" width="0.2" layer="21" curve="-253.7"/>
<text x="0" y="2.2" size="1.016" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-2.2" size="1.016" layer="27" align="top-center">&gt;VALUE</text>
</package>
</packages>
<symbols>
<symbol name="ESP32">
<wire x1="-10.16" y1="20.32" x2="10.16" y2="20.32" width="0.254" layer="94"/>
<wire x1="10.16" y1="20.32" x2="10.16" y2="-20.32" width="0.254" layer="94"/>
<wire x1="10.16" y1="-20.32" x2="-10.16" y2="-20.32" width="0.254" layer="94"/>
<wire x1="-10.16" y1="-20.32" x2="-10.16" y2="20.32" width="0.254" layer="94"/>
<text x="-10.16" y="21.12" size="1.778" layer="95">&gt;NAME</text>
<text x="-10.16" y="-22.92" size="1.778" layer="96">&gt;VALUE</text>
<pin name="EN" x="-12.7" y="17.78" length="short" direction="pas" rot="R0"/>
<pin name="VP" x="-12.7" y="15.24" length="short" direction="pas" rot="R0"/>
<pin name="VN" x="-12.7" y="12.7" length="short" direction="pas" rot="R0"/>
<pin name="D34" x="-12.7" y="10.16" length="short" direction="pas" rot="R0"/>
<pin name="D35" x="-12.7" y="7.62" length="short" direction="pas" rot="R0"/>
<pin name="D32" x="-12.7" y="5.08" length="short" direction="pas" rot="R0"/>
<pin name="D33" x="-12.7" y="2.54" length="short" direction="pas" rot="R0"/>
<pin name="D25" x="-12.7" y="0" length="short" direction="pas" rot="R0"/>
<pin name="D26" x="-12.7" y="-2.54" length="short" direction="pas" rot="R0"/>
<pin name="D27" x="-12.7" y="-5.08" length="short" direction="pas" rot="R0"/>
<pin name="D14" x="-12.7" y="-7.62" length="short" direction="pas" rot="R0"/>
<pin name="D12" x="-12.7" y="-10.16" length="short" direction="pas" rot="R0"/>
<pin name="D13" x="-12.7" y="-12.7" length="short" direction="pas" rot="R0"/>
<pin name="GND@1" x="-12.7" y="-15.24" length="short" direction="pas" rot="R0"/>
<pin name="VIN" x="-12.7" y="-17.78" length="short" direction="pas" rot="R0"/>
<pin name="D23" x="12.7" y="17.78" length="short" direction="pas" rot="R180"/>
<pin name="D22" x="12.7" y="15.24" length="short" direction="pas" rot="R180"/>
<pin name="TX0" x="12.7" y="12.7" length="short" direction="pas" rot="R180"/>
<pin name="RX0" x="12.7" y="10.16" length="short" direction="pas" rot="R180"/>
<pin name="D21" x="12.7" y="7.62" length="short" direction="pas" rot="R180"/>
<pin name="D19" x="12.7" y="5.08" length="short" direction="pas" rot="R180"/>
<pin name="D18" x="12.7" y="2.54" length="short" direction="pas" rot="R180"/>
<pin name="D5" x="12.7" y="0" length="short" direction="pas" rot="R180"/>
<pin name="TX2" x="12.7" y="-2.54" length="short" direction="pas" rot="R180"/>
<pin name="RX2" x="12.7" y="-5.08" length="short" direction="pas" rot="R180"/>
<pin name="D4" x="12.7" y="-7.62" length="short" direction="pas" rot="R180"/>
<pin name="D2" x="12.7" y="-10.16" length="short" direction="pas" rot="R180"/>
<pin name="D15" x="12.7" y="-12.7" length="short" direction="pas" rot="R180"/>
<pin name="GND@2" x="12.7" y="-15.24" length="short" direction="pas" rot="R180"/>
<pin name="3V3" x="12.7" y="-17.78" length="short" direction="pas" rot="R180"/>
</symbol>
<symbol name="HDR6">
<wire x1="-5.08" y1="8.89" x2="5.08" y2="8.89" width="0.254" layer="94"/>
<wire x1="5.08" y1="8.89" x2="5.08" y2="-8.89" width="0.254" layer="94"/>
<wire x1="5.08" y1="-8.89" x2="-5.08" y2="-8.89" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-8.89" x2="-5.08" y2="8.89" width="0.254" layer="94"/>
<text x="-5.08" y="9.69" size="1.778" layer="95">&gt;NAME</text>
<text x="-5.08" y="-11.49" size="1.778" layer="96">&gt;VALUE</text>
<pin name="1" x="-7.62" y="6.35" length="short" direction="pas" rot="R0"/>
<pin name="2" x="-7.62" y="3.81" length="short" direction="pas" rot="R0"/>
<pin name="3" x="-7.62" y="1.27" length="short" direction="pas" rot="R0"/>
<pin name="4" x="-7.62" y="-1.27" length="short" direction="pas" rot="R0"/>
<pin name="5" x="-7.62" y="-3.81" length="short" direction="pas" rot="R0"/>
<pin name="6" x="-7.62" y="-6.35" length="short" direction="pas" rot="R0"/>
</symbol>
<symbol name="HDR4">
<wire x1="-5.08" y1="6.35" x2="5.08" y2="6.35" width="0.254" layer="94"/>
<wire x1="5.08" y1="6.35" x2="5.08" y2="-6.35" width="0.254" layer="94"/>
<wire x1="5.08" y1="-6.35" x2="-5.08" y2="-6.35" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-6.35" x2="-5.08" y2="6.35" width="0.254" layer="94"/>
<text x="-5.08" y="7.15" size="1.778" layer="95">&gt;NAME</text>
<text x="-5.08" y="-8.95" size="1.778" layer="96">&gt;VALUE</text>
<pin name="1" x="-7.62" y="3.81" length="short" direction="pas" rot="R0"/>
<pin name="2" x="-7.62" y="1.27" length="short" direction="pas" rot="R0"/>
<pin name="3" x="-7.62" y="-1.27" length="short" direction="pas" rot="R0"/>
<pin name="4" x="-7.62" y="-3.81" length="short" direction="pas" rot="R0"/>
</symbol>
<symbol name="HDR4F">
<wire x1="-5.08" y1="6.35" x2="5.08" y2="6.35" width="0.254" layer="94"/>
<wire x1="5.08" y1="6.35" x2="5.08" y2="-6.35" width="0.254" layer="94"/>
<wire x1="5.08" y1="-6.35" x2="-5.08" y2="-6.35" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-6.35" x2="-5.08" y2="6.35" width="0.254" layer="94"/>
<text x="-5.08" y="7.15" size="1.778" layer="95">&gt;NAME</text>
<text x="-5.08" y="-8.95" size="1.778" layer="96">&gt;VALUE</text>
<pin name="1" x="-7.62" y="3.81" length="short" direction="pas" rot="R0"/>
<pin name="2" x="-7.62" y="1.27" length="short" direction="pas" rot="R0"/>
<pin name="3" x="-7.62" y="-1.27" length="short" direction="pas" rot="R0"/>
<pin name="4" x="-7.62" y="-3.81" length="short" direction="pas" rot="R0"/>
</symbol>
<symbol name="TERM3">
<wire x1="-5.08" y1="5.08" x2="5.08" y2="5.08" width="0.254" layer="94"/>
<wire x1="5.08" y1="5.08" x2="5.08" y2="-5.08" width="0.254" layer="94"/>
<wire x1="5.08" y1="-5.08" x2="-5.08" y2="-5.08" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-5.08" x2="-5.08" y2="5.08" width="0.254" layer="94"/>
<text x="-5.08" y="5.88" size="1.778" layer="95">&gt;NAME</text>
<text x="-5.08" y="-7.68" size="1.778" layer="96">&gt;VALUE</text>
<pin name="1" x="-7.62" y="2.54" length="short" direction="pas" rot="R0"/>
<pin name="2" x="-7.62" y="0" length="short" direction="pas" rot="R0"/>
<pin name="3" x="-7.62" y="-2.54" length="short" direction="pas" rot="R0"/>
</symbol>
<symbol name="TERM2">
<wire x1="-5.08" y1="3.81" x2="5.08" y2="3.81" width="0.254" layer="94"/>
<wire x1="5.08" y1="3.81" x2="5.08" y2="-3.81" width="0.254" layer="94"/>
<wire x1="5.08" y1="-3.81" x2="-5.08" y2="-3.81" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-3.81" x2="-5.08" y2="3.81" width="0.254" layer="94"/>
<text x="-5.08" y="4.61" size="1.778" layer="95">&gt;NAME</text>
<text x="-5.08" y="-6.41" size="1.778" layer="96">&gt;VALUE</text>
<pin name="1" x="-7.62" y="1.27" length="short" direction="pas" rot="R0"/>
<pin name="2" x="-7.62" y="-1.27" length="short" direction="pas" rot="R0"/>
</symbol>
<symbol name="L7805">
<wire x1="-5.08" y1="3.81" x2="5.08" y2="3.81" width="0.254" layer="94"/>
<wire x1="5.08" y1="3.81" x2="5.08" y2="-3.81" width="0.254" layer="94"/>
<wire x1="5.08" y1="-3.81" x2="-5.08" y2="-3.81" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-3.81" x2="-5.08" y2="3.81" width="0.254" layer="94"/>
<text x="-5.08" y="4.61" size="1.778" layer="95">&gt;NAME</text>
<text x="-5.08" y="-6.41" size="1.778" layer="96">&gt;VALUE</text>
<pin name="IN" x="-7.62" y="1.27" length="short" direction="pas" rot="R0"/>
<pin name="GND" x="-7.62" y="-1.27" length="short" direction="pas" rot="R0"/>
<pin name="OUT" x="7.62" y="1.27" length="short" direction="pas" rot="R180"/>
</symbol>
<symbol name="CAP">
<wire x1="-5.08" y1="2.54" x2="5.08" y2="2.54" width="0.254" layer="94"/>
<wire x1="5.08" y1="2.54" x2="5.08" y2="-2.54" width="0.254" layer="94"/>
<wire x1="5.08" y1="-2.54" x2="-5.08" y2="-2.54" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-2.54" x2="-5.08" y2="2.54" width="0.254" layer="94"/>
<text x="-5.08" y="3.34" size="1.778" layer="95">&gt;NAME</text>
<text x="-5.08" y="-5.14" size="1.778" layer="96">&gt;VALUE</text>
<pin name="+" x="-7.62" y="0" length="short" direction="pas" rot="R0"/>
<pin name="-" x="7.62" y="0" length="short" direction="pas" rot="R180"/>
</symbol>
<symbol name="RES">
<wire x1="-5.08" y1="2.54" x2="5.08" y2="2.54" width="0.254" layer="94"/>
<wire x1="5.08" y1="2.54" x2="5.08" y2="-2.54" width="0.254" layer="94"/>
<wire x1="5.08" y1="-2.54" x2="-5.08" y2="-2.54" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-2.54" x2="-5.08" y2="2.54" width="0.254" layer="94"/>
<text x="-5.08" y="3.34" size="1.778" layer="95">&gt;NAME</text>
<text x="-5.08" y="-5.14" size="1.778" layer="96">&gt;VALUE</text>
<pin name="1" x="-7.62" y="0" length="short" direction="pas" rot="R0"/>
<pin name="2" x="7.62" y="0" length="short" direction="pas" rot="R180"/>
</symbol>
<symbol name="BC337">
<wire x1="-5.08" y1="3.81" x2="5.08" y2="3.81" width="0.254" layer="94"/>
<wire x1="5.08" y1="3.81" x2="5.08" y2="-3.81" width="0.254" layer="94"/>
<wire x1="5.08" y1="-3.81" x2="-5.08" y2="-3.81" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-3.81" x2="-5.08" y2="3.81" width="0.254" layer="94"/>
<text x="-5.08" y="4.61" size="1.778" layer="95">&gt;NAME</text>
<text x="-5.08" y="-6.41" size="1.778" layer="96">&gt;VALUE</text>
<pin name="B" x="-7.62" y="1.27" length="short" direction="pas" rot="R0"/>
<pin name="C" x="7.62" y="1.27" length="short" direction="pas" rot="R180"/>
<pin name="E" x="7.62" y="-1.27" length="short" direction="pas" rot="R180"/>
</symbol>
<symbol name="BUZZERHDR">
<wire x1="-5.08" y1="2.54" x2="5.08" y2="2.54" width="0.254" layer="94"/>
<wire x1="5.08" y1="2.54" x2="5.08" y2="-2.54" width="0.254" layer="94"/>
<wire x1="5.08" y1="-2.54" x2="-5.08" y2="-2.54" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-2.54" x2="-5.08" y2="2.54" width="0.254" layer="94"/>
<text x="-5.08" y="3.34" size="1.778" layer="95">&gt;NAME</text>
<text x="-5.08" y="-5.14" size="1.778" layer="96">&gt;VALUE</text>
<pin name="+" x="-7.62" y="0" length="short" direction="pas" rot="R0"/>
<pin name="-" x="7.62" y="0" length="short" direction="pas" rot="R180"/>
</symbol>
<symbol name="JUMPER">
<wire x1="-5.08" y1="2.54" x2="5.08" y2="2.54" width="0.254" layer="94"/>
<wire x1="5.08" y1="2.54" x2="5.08" y2="-2.54" width="0.254" layer="94"/>
<wire x1="5.08" y1="-2.54" x2="-5.08" y2="-2.54" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-2.54" x2="-5.08" y2="2.54" width="0.254" layer="94"/>
<text x="-5.08" y="3.34" size="1.778" layer="95">&gt;NAME</text>
<text x="-5.08" y="-5.14" size="1.778" layer="96">&gt;VALUE</text>
<pin name="1" x="-7.62" y="0" length="short" direction="pas" rot="R0"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="ESP32" prefix="U">
<description>ESP32 DOIT DevKit V1 30 pin</description>
<gates>
<gate name="G$1" symbol="ESP32" x="0" y="0"/>
</gates>
<devices>
<device name="" package="ESP32_DEVKIT_V1_30">
<connects>
<connect gate="G$1" pin="3V3" pad="R15"/>
<connect gate="G$1" pin="D12" pad="L12"/>
<connect gate="G$1" pin="D13" pad="L13"/>
<connect gate="G$1" pin="D14" pad="L11"/>
<connect gate="G$1" pin="D15" pad="R13"/>
<connect gate="G$1" pin="D18" pad="R7"/>
<connect gate="G$1" pin="D19" pad="R6"/>
<connect gate="G$1" pin="D2" pad="R12"/>
<connect gate="G$1" pin="D21" pad="R5"/>
<connect gate="G$1" pin="D22" pad="R2"/>
<connect gate="G$1" pin="D23" pad="R1"/>
<connect gate="G$1" pin="D25" pad="L8"/>
<connect gate="G$1" pin="D26" pad="L9"/>
<connect gate="G$1" pin="D27" pad="L10"/>
<connect gate="G$1" pin="D32" pad="L6"/>
<connect gate="G$1" pin="D33" pad="L7"/>
<connect gate="G$1" pin="D34" pad="L4"/>
<connect gate="G$1" pin="D35" pad="L5"/>
<connect gate="G$1" pin="D4" pad="R11"/>
<connect gate="G$1" pin="D5" pad="R8"/>
<connect gate="G$1" pin="EN" pad="L1"/>
<connect gate="G$1" pin="GND@1" pad="L14"/>
<connect gate="G$1" pin="GND@2" pad="R14"/>
<connect gate="G$1" pin="RX0" pad="R4"/>
<connect gate="G$1" pin="RX2" pad="R10"/>
<connect gate="G$1" pin="TX0" pad="R3"/>
<connect gate="G$1" pin="TX2" pad="R9"/>
<connect gate="G$1" pin="VIN" pad="L15"/>
<connect gate="G$1" pin="VN" pad="L3"/>
<connect gate="G$1" pin="VP" pad="L2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="HDR6" prefix="J">
<description>Header 1x6 2.54</description>
<gates>
<gate name="G$1" symbol="HDR6" x="0" y="0"/>
</gates>
<devices>
<device name="" package="HDR1X6_V">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="HDR4" prefix="J">
<description>Header 1x4 2.54 (male / JST-XH / KF2510)</description>
<gates>
<gate name="G$1" symbol="HDR4" x="0" y="0"/>
</gates>
<devices>
<device name="" package="HDR1X4_H">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="HDR4F" prefix="J">
<description>Socket 1x4 female untuk HC-SR04</description>
<gates>
<gate name="G$1" symbol="HDR4F" x="0" y="0"/>
</gates>
<devices>
<device name="" package="HDR1X4_H">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="TERM3" prefix="J">
<description>Terminal screw 3P 5.08</description>
<gates>
<gate name="G$1" symbol="TERM3" x="0" y="0"/>
</gates>
<devices>
<device name="" package="TERM3_508">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="TERM2" prefix="J">
<description>Terminal screw 2P 5.08</description>
<gates>
<gate name="G$1" symbol="TERM2" x="0" y="0"/>
</gates>
<devices>
<device name="" package="TERM2_508">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="L7805" prefix="U">
<description>Regulator 5V TO-220</description>
<gates>
<gate name="G$1" symbol="L7805" x="0" y="0"/>
</gates>
<devices>
<device name="" package="TO220V">
<connects>
<connect gate="G$1" pin="GND" pad="2"/>
<connect gate="G$1" pin="IN" pad="1"/>
<connect gate="G$1" pin="OUT" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="CAP" prefix="C">
<description>Kapasitor 1uF radial</description>
<gates>
<gate name="G$1" symbol="CAP" x="0" y="0"/>
</gates>
<devices>
<device name="" package="CAP_RAD_2.54">
<connects>
<connect gate="G$1" pin="+" pad="1"/>
<connect gate="G$1" pin="-" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="RES" prefix="R">
<description>Resistor 1/4W</description>
<gates>
<gate name="G$1" symbol="RES" x="0" y="0"/>
</gates>
<devices>
<device name="" package="RES_AX_10.16">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="BC337" prefix="Q">
<description>NPN BC337</description>
<gates>
<gate name="G$1" symbol="BC337" x="0" y="0"/>
</gates>
<devices>
<device name="" package="TO92_INLINE">
<connects>
<connect gate="G$1" pin="B" pad="2"/>
<connect gate="G$1" pin="C" pad="1"/>
<connect gate="G$1" pin="E" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="BUZZERHDR" prefix="J">
<description>Header 2 pin ke buzzer</description>
<gates>
<gate name="G$1" symbol="BUZZERHDR" x="0" y="0"/>
</gates>
<devices>
<device name="" package="HDR1X2_BZ">
<connects>
<connect gate="G$1" pin="+" pad="1"/>
<connect gate="G$1" pin="-" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="JUMPER" prefix="JP">
<description>Jumper kabel (2 pad satu net)</description>
<gates>
<gate name="G$1" symbol="JUMPER" x="0" y="0"/>
</gates>
<devices>
<device name="" package="JUMPER_WIRE">
<connects>
<connect gate="G$1" pin="1" pad="1 2"/>
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
<attributes/>
<variantdefs/>
<classes>
<class number="0" name="default" width="0" drill="0"/>
<class number="1" name="power" width="0" drill="0"/>
</classes>
<parts>
<part name="U1" library="arca" deviceset="ESP32" device="" value="ESP32 DevKit V1"/>
<part name="J4" library="arca" deviceset="HDR6" device="" value="L298N IN"/>
<part name="J5" library="arca" deviceset="HDR4" device="" value="US1"/>
<part name="J6" library="arca" deviceset="HDR4" device="" value="US2"/>
<part name="J7" library="arca" deviceset="HDR4" device="" value="US3"/>
<part name="J8" library="arca" deviceset="HDR4" device="" value="US4"/>
<part name="J1" library="arca" deviceset="TERM3" device="" value="BATERAI 2S"/>
<part name="J2" library="arca" deviceset="TERM2" device="" value="CONVEYOR"/>
<part name="J3" library="arca" deviceset="TERM2" device="" value="L298N PWR"/>
<part name="U2" library="arca" deviceset="L7805" device="" value="L7805"/>
<part name="C1" library="arca" deviceset="CAP" device="" value="1uF"/>
<part name="C2" library="arca" deviceset="CAP" device="" value="1uF"/>
<part name="R1" library="arca" deviceset="RES" device="" value="1k"/>
<part name="Q1" library="arca" deviceset="BC337" device="" value="BC337"/>
<part name="J9" library="arca" deviceset="BUZZERHDR" device="" value="BUZZER"/>
<part name="JP1" library="arca" deviceset="JUMPER" device="" value="JUMPER"/>
</parts>
<sheets>
<sheet>
<plain>
<text x="5.08" y="5.08" size="2.54" layer="97">arca-main — ARCA IoT River Cleaning Boat (dibuat otomatis dari design.py)</text>
</plain>
<instances>
<instance part="U1" gate="G$1" x="55.88" y="200.66"/>
<instance part="J4" gate="G$1" x="121.92" y="200.66"/>
<instance part="J5" gate="G$1" x="182.88" y="200.66"/>
<instance part="J6" gate="G$1" x="243.84" y="200.66"/>
<instance part="J7" gate="G$1" x="304.8" y="200.66"/>
<instance part="J8" gate="G$1" x="50.8" y="127"/>
<instance part="J1" gate="G$1" x="111.76" y="127"/>
<instance part="U2" gate="G$1" x="172.72" y="127"/>
<instance part="Q1" gate="G$1" x="233.68" y="127"/>
<instance part="J2" gate="G$1" x="294.64" y="127"/>
<instance part="J3" gate="G$1" x="50.8" y="81.28"/>
<instance part="C1" gate="G$1" x="111.76" y="81.28"/>
<instance part="C2" gate="G$1" x="172.72" y="81.28"/>
<instance part="R1" gate="G$1" x="233.68" y="81.28"/>
<instance part="J9" gate="G$1" x="294.64" y="81.28"/>
<instance part="JP1" gate="G$1" x="50.8" y="40.64"/>
</instances>
<busses/>
<nets>
<net name="VBAT" class="1">
<segment>
<pinref part="J1" gate="G$1" pin="3"/>
<wire x1="104.14" y1="124.46" x2="96.52" y2="124.46" width="0.1524" layer="91"/>
<label x="96.52" y="124.46" size="1.27" layer="95" align="bottom-right"/>
</segment>
<segment>
<pinref part="J3" gate="G$1" pin="2"/>
<wire x1="43.18" y1="80.01" x2="35.56" y2="80.01" width="0.1524" layer="91"/>
<label x="35.56" y="80.01" size="1.27" layer="95" align="bottom-right"/>
</segment>
<segment>
<pinref part="U2" gate="G$1" pin="IN"/>
<wire x1="165.1" y1="128.27" x2="157.48" y2="128.27" width="0.1524" layer="91"/>
<label x="157.48" y="128.27" size="1.27" layer="95" align="bottom-right"/>
</segment>
<segment>
<pinref part="C1" gate="G$1" pin="+"/>
<wire x1="104.14" y1="81.28" x2="96.52" y2="81.28" width="0.1524" layer="91"/>
<label x="96.52" y="81.28" size="1.27" layer="95" align="bottom-right"/>
</segment>
<segment>
<pinref part="U1" gate="G$1" pin="VIN"/>
<wire x1="43.18" y1="182.88" x2="35.56" y2="182.88" width="0.1524" layer="91"/>
<label x="35.56" y="182.88" size="1.27" layer="95" align="bottom-right"/>
</segment>
</net>
<net name="GND" class="1">
<segment>
<pinref part="J1" gate="G$1" pin="2"/>
<wire x1="104.14" y1="127" x2="96.52" y2="127" width="0.1524" layer="91"/>
<label x="96.52" y="127" size="1.27" layer="95" align="bottom-right"/>
</segment>
<segment>
<pinref part="J3" gate="G$1" pin="1"/>
<wire x1="43.18" y1="82.55" x2="35.56" y2="82.55" width="0.1524" layer="91"/>
<label x="35.56" y="82.55" size="1.27" layer="95" align="bottom-right"/>
</segment>
<segment>
<pinref part="J2" gate="G$1" pin="1"/>
<wire x1="287.02" y1="128.27" x2="279.4" y2="128.27" width="0.1524" layer="91"/>
<label x="279.4" y="128.27" size="1.27" layer="95" align="bottom-right"/>
</segment>
<segment>
<pinref part="U2" gate="G$1" pin="GND"/>
<wire x1="165.1" y1="125.73" x2="157.48" y2="125.73" width="0.1524" layer="91"/>
<label x="157.48" y="125.73" size="1.27" layer="95" align="bottom-right"/>
</segment>
<segment>
<pinref part="C1" gate="G$1" pin="-"/>
<wire x1="119.38" y1="81.28" x2="127" y2="81.28" width="0.1524" layer="91"/>
<label x="127" y="81.28" size="1.27" layer="95" align="bottom-left"/>
</segment>
<segment>
<pinref part="C2" gate="G$1" pin="-"/>
<wire x1="180.34" y1="81.28" x2="187.96" y2="81.28" width="0.1524" layer="91"/>
<label x="187.96" y="81.28" size="1.27" layer="95" align="bottom-left"/>
</segment>
<segment>
<pinref part="U1" gate="G$1" pin="GND@1"/>
<wire x1="43.18" y1="185.42" x2="35.56" y2="185.42" width="0.1524" layer="91"/>
<label x="35.56" y="185.42" size="1.27" layer="95" align="bottom-right"/>
</segment>
<segment>
<pinref part="Q1" gate="G$1" pin="E"/>
<wire x1="241.3" y1="125.73" x2="248.92" y2="125.73" width="0.1524" layer="91"/>
<label x="248.92" y="125.73" size="1.27" layer="95" align="bottom-left"/>
</segment>
<segment>
<pinref part="J5" gate="G$1" pin="3"/>
<wire x1="175.26" y1="199.39" x2="167.64" y2="199.39" width="0.1524" layer="91"/>
<label x="167.64" y="199.39" size="1.27" layer="95" align="bottom-right"/>
</segment>
<segment>
<pinref part="J6" gate="G$1" pin="3"/>
<wire x1="236.22" y1="199.39" x2="228.6" y2="199.39" width="0.1524" layer="91"/>
<label x="228.6" y="199.39" size="1.27" layer="95" align="bottom-right"/>
</segment>
<segment>
<pinref part="J7" gate="G$1" pin="3"/>
<wire x1="297.18" y1="199.39" x2="289.56" y2="199.39" width="0.1524" layer="91"/>
<label x="289.56" y="199.39" size="1.27" layer="95" align="bottom-right"/>
</segment>
<segment>
<pinref part="J8" gate="G$1" pin="3"/>
<wire x1="43.18" y1="125.73" x2="35.56" y2="125.73" width="0.1524" layer="91"/>
<label x="35.56" y="125.73" size="1.27" layer="95" align="bottom-right"/>
</segment>
</net>
<net name="MID" class="1">
<segment>
<pinref part="J1" gate="G$1" pin="1"/>
<wire x1="104.14" y1="129.54" x2="96.52" y2="129.54" width="0.1524" layer="91"/>
<label x="96.52" y="129.54" size="1.27" layer="95" align="bottom-right"/>
</segment>
<segment>
<pinref part="J2" gate="G$1" pin="2"/>
<wire x1="287.02" y1="125.73" x2="279.4" y2="125.73" width="0.1524" layer="91"/>
<label x="279.4" y="125.73" size="1.27" layer="95" align="bottom-right"/>
</segment>
</net>
<net name="+5V" class="1">
<segment>
<pinref part="U2" gate="G$1" pin="OUT"/>
<wire x1="180.34" y1="128.27" x2="187.96" y2="128.27" width="0.1524" layer="91"/>
<label x="187.96" y="128.27" size="1.27" layer="95" align="bottom-left"/>
</segment>
<segment>
<pinref part="C2" gate="G$1" pin="+"/>
<wire x1="165.1" y1="81.28" x2="157.48" y2="81.28" width="0.1524" layer="91"/>
<label x="157.48" y="81.28" size="1.27" layer="95" align="bottom-right"/>
</segment>
<segment>
<pinref part="J5" gate="G$1" pin="4"/>
<wire x1="175.26" y1="196.85" x2="167.64" y2="196.85" width="0.1524" layer="91"/>
<label x="167.64" y="196.85" size="1.27" layer="95" align="bottom-right"/>
</segment>
<segment>
<pinref part="J6" gate="G$1" pin="4"/>
<wire x1="236.22" y1="196.85" x2="228.6" y2="196.85" width="0.1524" layer="91"/>
<label x="228.6" y="196.85" size="1.27" layer="95" align="bottom-right"/>
</segment>
<segment>
<pinref part="J7" gate="G$1" pin="4"/>
<wire x1="297.18" y1="196.85" x2="289.56" y2="196.85" width="0.1524" layer="91"/>
<label x="289.56" y="196.85" size="1.27" layer="95" align="bottom-right"/>
</segment>
<segment>
<pinref part="J8" gate="G$1" pin="4"/>
<wire x1="43.18" y1="123.19" x2="35.56" y2="123.19" width="0.1524" layer="91"/>
<label x="35.56" y="123.19" size="1.27" layer="95" align="bottom-right"/>
</segment>
<segment>
<pinref part="JP1" gate="G$1" pin="1"/>
<wire x1="43.18" y1="40.64" x2="35.56" y2="40.64" width="0.1524" layer="91"/>
<label x="35.56" y="40.64" size="1.27" layer="95" align="bottom-right"/>
</segment>
<segment>
<pinref part="J9" gate="G$1" pin="+"/>
<wire x1="287.02" y1="81.28" x2="279.4" y2="81.28" width="0.1524" layer="91"/>
<label x="279.4" y="81.28" size="1.27" layer="95" align="bottom-right"/>
</segment>
</net>
<net name="BZ-" class="0">
<segment>
<pinref part="Q1" gate="G$1" pin="C"/>
<wire x1="241.3" y1="128.27" x2="248.92" y2="128.27" width="0.1524" layer="91"/>
<label x="248.92" y="128.27" size="1.27" layer="95" align="bottom-left"/>
</segment>
<segment>
<pinref part="J9" gate="G$1" pin="-"/>
<wire x1="302.26" y1="81.28" x2="309.88" y2="81.28" width="0.1524" layer="91"/>
<label x="309.88" y="81.28" size="1.27" layer="95" align="bottom-left"/>
</segment>
</net>
<net name="Q_BASE" class="0">
<segment>
<pinref part="Q1" gate="G$1" pin="B"/>
<wire x1="226.06" y1="128.27" x2="218.44" y2="128.27" width="0.1524" layer="91"/>
<label x="218.44" y="128.27" size="1.27" layer="95" align="bottom-right"/>
</segment>
<segment>
<pinref part="R1" gate="G$1" pin="2"/>
<wire x1="241.3" y1="81.28" x2="248.92" y2="81.28" width="0.1524" layer="91"/>
<label x="248.92" y="81.28" size="1.27" layer="95" align="bottom-left"/>
</segment>
</net>
<net name="BUZ" class="0">
<segment>
<pinref part="U1" gate="G$1" pin="D13"/>
<wire x1="43.18" y1="187.96" x2="35.56" y2="187.96" width="0.1524" layer="91"/>
<label x="35.56" y="187.96" size="1.27" layer="95" align="bottom-right"/>
</segment>
<segment>
<pinref part="R1" gate="G$1" pin="1"/>
<wire x1="226.06" y1="81.28" x2="218.44" y2="81.28" width="0.1524" layer="91"/>
<label x="218.44" y="81.28" size="1.27" layer="95" align="bottom-right"/>
</segment>
</net>
<net name="ENA" class="0">
<segment>
<pinref part="U1" gate="G$1" pin="D32"/>
<wire x1="43.18" y1="205.74" x2="35.56" y2="205.74" width="0.1524" layer="91"/>
<label x="35.56" y="205.74" size="1.27" layer="95" align="bottom-right"/>
</segment>
<segment>
<pinref part="J4" gate="G$1" pin="1"/>
<wire x1="114.3" y1="207.01" x2="106.68" y2="207.01" width="0.1524" layer="91"/>
<label x="106.68" y="207.01" size="1.27" layer="95" align="bottom-right"/>
</segment>
</net>
<net name="IN1" class="0">
<segment>
<pinref part="U1" gate="G$1" pin="D33"/>
<wire x1="43.18" y1="203.2" x2="35.56" y2="203.2" width="0.1524" layer="91"/>
<label x="35.56" y="203.2" size="1.27" layer="95" align="bottom-right"/>
</segment>
<segment>
<pinref part="J4" gate="G$1" pin="2"/>
<wire x1="114.3" y1="204.47" x2="106.68" y2="204.47" width="0.1524" layer="91"/>
<label x="106.68" y="204.47" size="1.27" layer="95" align="bottom-right"/>
</segment>
</net>
<net name="IN2" class="0">
<segment>
<pinref part="U1" gate="G$1" pin="D25"/>
<wire x1="43.18" y1="200.66" x2="35.56" y2="200.66" width="0.1524" layer="91"/>
<label x="35.56" y="200.66" size="1.27" layer="95" align="bottom-right"/>
</segment>
<segment>
<pinref part="J4" gate="G$1" pin="3"/>
<wire x1="114.3" y1="201.93" x2="106.68" y2="201.93" width="0.1524" layer="91"/>
<label x="106.68" y="201.93" size="1.27" layer="95" align="bottom-right"/>
</segment>
</net>
<net name="IN3" class="0">
<segment>
<pinref part="U1" gate="G$1" pin="D26"/>
<wire x1="43.18" y1="198.12" x2="35.56" y2="198.12" width="0.1524" layer="91"/>
<label x="35.56" y="198.12" size="1.27" layer="95" align="bottom-right"/>
</segment>
<segment>
<pinref part="J4" gate="G$1" pin="4"/>
<wire x1="114.3" y1="199.39" x2="106.68" y2="199.39" width="0.1524" layer="91"/>
<label x="106.68" y="199.39" size="1.27" layer="95" align="bottom-right"/>
</segment>
</net>
<net name="IN4" class="0">
<segment>
<pinref part="U1" gate="G$1" pin="D27"/>
<wire x1="43.18" y1="195.58" x2="35.56" y2="195.58" width="0.1524" layer="91"/>
<label x="35.56" y="195.58" size="1.27" layer="95" align="bottom-right"/>
</segment>
<segment>
<pinref part="J4" gate="G$1" pin="5"/>
<wire x1="114.3" y1="196.85" x2="106.68" y2="196.85" width="0.1524" layer="91"/>
<label x="106.68" y="196.85" size="1.27" layer="95" align="bottom-right"/>
</segment>
</net>
<net name="ENB" class="0">
<segment>
<pinref part="U1" gate="G$1" pin="D14"/>
<wire x1="43.18" y1="193.04" x2="35.56" y2="193.04" width="0.1524" layer="91"/>
<label x="35.56" y="193.04" size="1.27" layer="95" align="bottom-right"/>
</segment>
<segment>
<pinref part="J4" gate="G$1" pin="6"/>
<wire x1="114.3" y1="194.31" x2="106.68" y2="194.31" width="0.1524" layer="91"/>
<label x="106.68" y="194.31" size="1.27" layer="95" align="bottom-right"/>
</segment>
</net>
<net name="US1_ECHO" class="0">
<segment>
<pinref part="U1" gate="G$1" pin="D23"/>
<wire x1="68.58" y1="218.44" x2="76.2" y2="218.44" width="0.1524" layer="91"/>
<label x="76.2" y="218.44" size="1.27" layer="95" align="bottom-left"/>
</segment>
<segment>
<pinref part="J5" gate="G$1" pin="2"/>
<wire x1="175.26" y1="201.93" x2="167.64" y2="201.93" width="0.1524" layer="91"/>
<label x="167.64" y="201.93" size="1.27" layer="95" align="bottom-right"/>
</segment>
</net>
<net name="US1_TRIG" class="0">
<segment>
<pinref part="U1" gate="G$1" pin="D22"/>
<wire x1="68.58" y1="215.9" x2="76.2" y2="215.9" width="0.1524" layer="91"/>
<label x="76.2" y="215.9" size="1.27" layer="95" align="bottom-left"/>
</segment>
<segment>
<pinref part="J5" gate="G$1" pin="1"/>
<wire x1="175.26" y1="204.47" x2="167.64" y2="204.47" width="0.1524" layer="91"/>
<label x="167.64" y="204.47" size="1.27" layer="95" align="bottom-right"/>
</segment>
</net>
<net name="US2_ECHO" class="0">
<segment>
<pinref part="U1" gate="G$1" pin="D21"/>
<wire x1="68.58" y1="208.28" x2="76.2" y2="208.28" width="0.1524" layer="91"/>
<label x="76.2" y="208.28" size="1.27" layer="95" align="bottom-left"/>
</segment>
<segment>
<pinref part="J6" gate="G$1" pin="2"/>
<wire x1="236.22" y1="201.93" x2="228.6" y2="201.93" width="0.1524" layer="91"/>
<label x="228.6" y="201.93" size="1.27" layer="95" align="bottom-right"/>
</segment>
</net>
<net name="US2_TRIG" class="0">
<segment>
<pinref part="U1" gate="G$1" pin="D19"/>
<wire x1="68.58" y1="205.74" x2="76.2" y2="205.74" width="0.1524" layer="91"/>
<label x="76.2" y="205.74" size="1.27" layer="95" align="bottom-left"/>
</segment>
<segment>
<pinref part="J6" gate="G$1" pin="1"/>
<wire x1="236.22" y1="204.47" x2="228.6" y2="204.47" width="0.1524" layer="91"/>
<label x="228.6" y="204.47" size="1.27" layer="95" align="bottom-right"/>
</segment>
</net>
<net name="US3_ECHO" class="0">
<segment>
<pinref part="U1" gate="G$1" pin="D18"/>
<wire x1="68.58" y1="203.2" x2="76.2" y2="203.2" width="0.1524" layer="91"/>
<label x="76.2" y="203.2" size="1.27" layer="95" align="bottom-left"/>
</segment>
<segment>
<pinref part="J7" gate="G$1" pin="2"/>
<wire x1="297.18" y1="201.93" x2="289.56" y2="201.93" width="0.1524" layer="91"/>
<label x="289.56" y="201.93" size="1.27" layer="95" align="bottom-right"/>
</segment>
</net>
<net name="US3_TRIG" class="0">
<segment>
<pinref part="U1" gate="G$1" pin="TX2"/>
<wire x1="68.58" y1="198.12" x2="76.2" y2="198.12" width="0.1524" layer="91"/>
<label x="76.2" y="198.12" size="1.27" layer="95" align="bottom-left"/>
</segment>
<segment>
<pinref part="J7" gate="G$1" pin="1"/>
<wire x1="297.18" y1="204.47" x2="289.56" y2="204.47" width="0.1524" layer="91"/>
<label x="289.56" y="204.47" size="1.27" layer="95" align="bottom-right"/>
</segment>
</net>
<net name="US4_ECHO" class="0">
<segment>
<pinref part="U1" gate="G$1" pin="RX2"/>
<wire x1="68.58" y1="195.58" x2="76.2" y2="195.58" width="0.1524" layer="91"/>
<label x="76.2" y="195.58" size="1.27" layer="95" align="bottom-left"/>
</segment>
<segment>
<pinref part="J8" gate="G$1" pin="2"/>
<wire x1="43.18" y1="128.27" x2="35.56" y2="128.27" width="0.1524" layer="91"/>
<label x="35.56" y="128.27" size="1.27" layer="95" align="bottom-right"/>
</segment>
</net>
<net name="US4_TRIG" class="0">
<segment>
<pinref part="U1" gate="G$1" pin="D4"/>
<wire x1="68.58" y1="193.04" x2="76.2" y2="193.04" width="0.1524" layer="91"/>
<label x="76.2" y="193.04" size="1.27" layer="95" align="bottom-left"/>
</segment>
<segment>
<pinref part="J8" gate="G$1" pin="1"/>
<wire x1="43.18" y1="130.81" x2="35.56" y2="130.81" width="0.1524" layer="91"/>
<label x="35.56" y="130.81" size="1.27" layer="95" align="bottom-right"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
