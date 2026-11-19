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
<package name="RES_V_2.54">
<description>Resistor 1/4 W berdiri, pitch 2.54 (badan di atas pad 1)</description>
<pad name="1" x="0" y="1.27" drill="0.9" diameter="1.7" shape="round"/>
<pad name="2" x="0" y="-1.27" drill="0.9" diameter="1.7" shape="round"/>
<wire x1="0" y1="0.02" x2="0" y2="-0.4" width="0.2" layer="21"/>
<circle x="0" y="1.27" radius="1.25" width="0.2" layer="21"/>
<text x="1.6" y="0" size="1.016" layer="51" align="center-left">&gt;NAME</text>
<text x="0" y="-3.47" size="1.016" layer="27" align="top-center">&gt;VALUE</text>
</package>
</packages>
<symbols>
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
<symbol name="RESV">
<wire x1="-5.08" y1="2.54" x2="5.08" y2="2.54" width="0.254" layer="94"/>
<wire x1="5.08" y1="2.54" x2="5.08" y2="-2.54" width="0.254" layer="94"/>
<wire x1="5.08" y1="-2.54" x2="-5.08" y2="-2.54" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-2.54" x2="-5.08" y2="2.54" width="0.254" layer="94"/>
<text x="-5.08" y="3.34" size="1.778" layer="95">&gt;NAME</text>
<text x="-5.08" y="-5.14" size="1.778" layer="96">&gt;VALUE</text>
<pin name="1" x="-7.62" y="0" length="short" direction="pas" rot="R0"/>
<pin name="2" x="7.62" y="0" length="short" direction="pas" rot="R180"/>
</symbol>
</symbols>
<devicesets>
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
<deviceset name="RESV" prefix="R">
<description>Resistor 1/4W berdiri</description>
<gates>
<gate name="G$1" symbol="RESV" x="0" y="0"/>
</gates>
<devices>
<device name="" package="RES_V_2.54">
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
<part name="J2" library="arca" deviceset="HDR4F" device="" value="HC-SR04"/>
<part name="J1" library="arca" deviceset="HDR4" device="" value="KE MAIN"/>
<part name="R1" library="arca" deviceset="RESV" device="" value="470"/>
<part name="R2" library="arca" deviceset="RESV" device="" value="1k"/>
</parts>
<sheets>
<sheet>
<plain>
<text x="5.08" y="5.08" size="2.54" layer="97">arca-sensor — ARCA IoT River Cleaning Boat (dibuat otomatis dari design.py)</text>
</plain>
<instances>
<instance part="J2" gate="G$1" x="50.8" y="200.66"/>
<instance part="J1" gate="G$1" x="111.76" y="200.66"/>
<instance part="R1" gate="G$1" x="172.72" y="200.66"/>
<instance part="R2" gate="G$1" x="233.68" y="200.66"/>
</instances>
<busses/>
<nets>
<net name="+5V" class="1">
<segment>
<pinref part="J2" gate="G$1" pin="1"/>
<wire x1="43.18" y1="204.47" x2="35.56" y2="204.47" width="0.1524" layer="91"/>
<label x="35.56" y="204.47" size="1.27" layer="95" align="bottom-right"/>
</segment>
<segment>
<pinref part="J1" gate="G$1" pin="4"/>
<wire x1="104.14" y1="196.85" x2="96.52" y2="196.85" width="0.1524" layer="91"/>
<label x="96.52" y="196.85" size="1.27" layer="95" align="bottom-right"/>
</segment>
</net>
<net name="TRIG" class="0">
<segment>
<pinref part="J2" gate="G$1" pin="2"/>
<wire x1="43.18" y1="201.93" x2="35.56" y2="201.93" width="0.1524" layer="91"/>
<label x="35.56" y="201.93" size="1.27" layer="95" align="bottom-right"/>
</segment>
<segment>
<pinref part="J1" gate="G$1" pin="1"/>
<wire x1="104.14" y1="204.47" x2="96.52" y2="204.47" width="0.1524" layer="91"/>
<label x="96.52" y="204.47" size="1.27" layer="95" align="bottom-right"/>
</segment>
</net>
<net name="ECHO_5V" class="0">
<segment>
<pinref part="J2" gate="G$1" pin="3"/>
<wire x1="43.18" y1="199.39" x2="35.56" y2="199.39" width="0.1524" layer="91"/>
<label x="35.56" y="199.39" size="1.27" layer="95" align="bottom-right"/>
</segment>
<segment>
<pinref part="R1" gate="G$1" pin="1"/>
<wire x1="165.1" y1="200.66" x2="157.48" y2="200.66" width="0.1524" layer="91"/>
<label x="157.48" y="200.66" size="1.27" layer="95" align="bottom-right"/>
</segment>
</net>
<net name="ECHO" class="0">
<segment>
<pinref part="R1" gate="G$1" pin="2"/>
<wire x1="180.34" y1="200.66" x2="187.96" y2="200.66" width="0.1524" layer="91"/>
<label x="187.96" y="200.66" size="1.27" layer="95" align="bottom-left"/>
</segment>
<segment>
<pinref part="R2" gate="G$1" pin="1"/>
<wire x1="226.06" y1="200.66" x2="218.44" y2="200.66" width="0.1524" layer="91"/>
<label x="218.44" y="200.66" size="1.27" layer="95" align="bottom-right"/>
</segment>
<segment>
<pinref part="J1" gate="G$1" pin="2"/>
<wire x1="104.14" y1="201.93" x2="96.52" y2="201.93" width="0.1524" layer="91"/>
<label x="96.52" y="201.93" size="1.27" layer="95" align="bottom-right"/>
</segment>
</net>
<net name="GND" class="1">
<segment>
<pinref part="J2" gate="G$1" pin="4"/>
<wire x1="43.18" y1="196.85" x2="35.56" y2="196.85" width="0.1524" layer="91"/>
<label x="35.56" y="196.85" size="1.27" layer="95" align="bottom-right"/>
</segment>
<segment>
<pinref part="R2" gate="G$1" pin="2"/>
<wire x1="241.3" y1="200.66" x2="248.92" y2="200.66" width="0.1524" layer="91"/>
<label x="248.92" y="200.66" size="1.27" layer="95" align="bottom-left"/>
</segment>
<segment>
<pinref part="J1" gate="G$1" pin="3"/>
<wire x1="104.14" y1="199.39" x2="96.52" y2="199.39" width="0.1524" layer="91"/>
<label x="96.52" y="199.39" size="1.27" layer="95" align="bottom-right"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
