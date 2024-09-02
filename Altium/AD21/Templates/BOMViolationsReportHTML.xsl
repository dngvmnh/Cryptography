<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version='1.0' xmlns:xsl='http://www.w3.org/1999/XSL/Transform'>
<xsl:template match="BomViolationsReport">
    <html>
    <head>
    <style type="text/css">
        h1, h2, h3, h4, h5, h6 {
			font-family : segoe ui;
			color : black;
			background-color : #EDE7D9;
            padding: 0.3em;
        }

		h1 {
			font-size: 1.2em;
		}		

		h2 {
			font-size: 1.2em;
		}

        body {
			font-family : segoe ui;
        }

        td, th {
            padding: 0.5em;
			text-align : left;
			width: 10em;
        }
        th {
			background-color : #EEEEEE;

        }
        th.column1, td.column1 {
            text-align: left;
            width : auto;
        }
        table {
            width : 100%;
			font-size: 0.9em;
        }

        .DRC_summary_header {
            padding-bottom : 0.1em;
            border : 0px solid black;
            width: 100%;
			align: left;
        }

        .DRC_summary_header_col1,
        .DRC_summary_header_col2,
        .DRC_summary_header_col3  {
            color : black;
            font-size:100%;
                        padding : 0em;
            padding-top : 0.2em;
            padding-bottom 0.2em;
            border : 0px solid black;
            vertical-align: top;
			text-align: left;
        }

        .DRC_summary_header_col1 {
			font-weight: bold;
			width: 8em;
        }

        .DRC_summary_header_col2 {
			width: 0.1em;
		
        }

        .DRC_summary_header_col3 {
			width : auto;
        }

        .header_holder  {
        Width = 100%;
        border = 0px solid green;
        padding = 0;
        }


        .front_matter, .front_matter_column1, .front_matter_column2, .front_matter_column3
                {
            left:0;
            top:0;
			padding: 0em;
            padding-top : 0.1em;
            border : 0px solid black;
            width : 100%;
            vertical-align: top;
            text-align: left;
        }

        .front_matter_column1 {
            width : 8em;
			font-weight: bold;
        }

        .front_matter_column2 {
            width: 0.1em;
        }

        .front_matter_column3 {
            width         : auto;
        }

        .total_column1, .total_column {
            font-weight : bold;
        }
        .total_column1 {
			text-align : left;
        }
        .warning, .error {
            color : red;
            font-weight : bold;
        }
        tr.onmouseout_odd {
			background-color : #white;
        }
        tr.onmouseout_even {
			background-color : #FAFAFA;
        }
        tr.onmouseover_odd, tr.onmouseover_even {
			background-color : #EEEEEE;
        }
        a:link, a:visited, .q a:link,.q a:active,.q {
            color: #21489e;
        }
        a:link.callback, a:visited.callback {
            color: #21489e;
        }
        p.contents_level1 {
            font-weight : bold;
            font-size : 110%;
            margin : 0.5em;
        }
        p.contents_level2 {
            position : relative;
            left : 20px;
            margin : 0.5em;
        }
    </style>
    </head>
    <body onload="">
        <xsl:call-template name="process_body"/>
    </body>
    </html>
</xsl:template>

<xsl:template name="process_body">
    <img ALT="Altium">
        <xsl:attribute name="src">
			file://<xsl:value-of select="ResourcePath"/>AD_logo.png
        </xsl:attribute>
    </img>

    <h1>BOM Violations Report</h1>

    <table class="header_holder">
       <td class="column1">
        <table class="front_matter">
            <xsl:if test="Date">
                <tr class="front_matter">
                    <td class="front_matter_column1">Date:</td>
                    <td class="front_matter_column2"></td>
                    <td class="front_matter_column3"><xsl:apply-templates select="Date"/></td>
                </tr>
            </xsl:if>

            <xsl:if test="Time">
                <tr class="front_matter">
                    <td class="front_matter_column1">Time:</td>
                    <td class="front_matter_column2"></td>
                    <td class="front_matter_column3"><xsl:apply-templates select="Time"/></td>
                </tr>
            </xsl:if>

            <xsl:if test="ElapsedTime">
                <tr class="front_matter">
                    <td class="front_matter_column1">Elapsed Time:</td>
                    <td class="front_matter_column2"></td>
                    <td class="front_matter_column3"><xsl:apply-templates select="ElapsedTime"/></td>
                </tr>
            </xsl:if>

            <xsl:if test="Filename">
                <tr class="front_matter">
                    <td class="front_matter_column1">Filename:</td>
                    <td class="front_matter_column2"></td>
                    <td class="front_matter_column3"><xsl:apply-templates select="Filename"/></td>
                </tr>
            </xsl:if>
        </table>
       </td>
        <td class="column2">
            <table class="DRC_summary_header">
                <xsl:for-each select="Violations/Headers/Header">
                    <tr>
                        <td class="DRC_summary_header_col1"><xsl:value-of select="Name"/>:</td>
                        <td class="DRC_summary_header_col2"></td>
                        <xsl:variable name="issue_level" select="Level"/>
                        <xsl:variable name="problemCount" select="count(/BomViolationsReport/Violations/Issues/ViolationsIssue[Level = $issue_level]/Designators/Designator)" />
                        <xsl:choose>
                            <xsl:when test="$problemCount > 0"><td class="DRC_summary_header_col3" style="color : red"> <xsl:value-of select="$problemCount"/></td></xsl:when>
                            <xsl:otherwise><td class="DRC_summary_header_col3"><xsl:value-of select="$problemCount"/></td></xsl:otherwise>
                         </xsl:choose>
                    </tr>
                </xsl:for-each>
            </table>
        </td>
    </table>

    <h2>Summary</h2>

    <xsl:for-each select="Violations/Headers/Header">
        <table>
            <tr>
                <th class="column1"><xsl:value-of select="Name"/>:</th>
                <th class="column2">Count</th>
            </tr>
            <xsl:variable name="issue_level" select="Level"/>
            <xsl:for-each select="/BomViolationsReport/Violations/Issues/ViolationsIssue">
                <xsl:if test="Level = $issue_level">
                    <xsl:element name="tr">
                        <xsl:call-template name="classify_row_even_or_odd"/>
                        <xsl:element name="td">
                            <xsl:call-template name="apply_column_index_attribute">
                                <xsl:with-param name="index">1</xsl:with-param>
                            </xsl:call-template>
                            <xsl:element name="a">
                                <xsl:attribute name="href">#<xsl:value-of select="generate-id(.)" /></xsl:attribute>
                                <xsl:apply-templates select="Name"/>
                            </xsl:element>
                        </xsl:element>
                        <xsl:element name="td">
                            <xsl:call-template name="apply_column_index_attribute">
                                <xsl:with-param name="index">2</xsl:with-param>
                            </xsl:call-template>
                            <xsl:value-of select="count(Designators/Designator)"/>
                        </xsl:element>
                    </xsl:element>
                </xsl:if>
            </xsl:for-each>
            <tr>
                <td style="font-weight : bold; text-align : right">
                    <xsl:call-template name="apply_column_index_attribute">
                        <xsl:with-param name="index">1</xsl:with-param>
                    </xsl:call-template>Total</td>
                <td style="font-weight : bold">
                    <xsl:call-template name="apply_column_index_attribute">
                        <xsl:with-param name="index">2</xsl:with-param>
                    </xsl:call-template>
                    <xsl:value-of select="count(/BomViolationsReport/Violations/Issues/ViolationsIssue[Level = $issue_level]/Designators/Designator)"/>
                </td>
            </tr>
        </table>
        <br/>
    </xsl:for-each>
    
    <xsl:for-each select="/BomViolationsReport/Violations/Headers/Header">
        <xsl:variable name="issue_level" select="Level"/>
        <xsl:for-each select="/BomViolationsReport/Violations/Issues/ViolationsIssue">
            <xsl:if test="Level = $issue_level">
                <xsl:if test="count(Designators/Designator) &gt; 0">
                    <table>
                        <tr>
                            <th>
                                <xsl:element name="a">
                                    <xsl:attribute name="name"><xsl:value-of select="generate-id(.)" /></xsl:attribute>
                                    <xsl:attribute name="style">text-align : left</xsl:attribute>
                                    <xsl:attribute name="colspan">1</xsl:attribute>
                                    <xsl:call-template name="callback"/>
                                </xsl:element>
                            </th>
                        </tr>
                        <tr>
                            <td>
                                <xsl:attribute name="class">column1</xsl:attribute>
                                <xsl:for-each select="Designators/Designator">
                                    <xsl:element name="a">
                                        <xsl:call-template name="callback"/>
                                    </xsl:element>
                                    <xsl:if test="position() != last()">
                                        <xsl:text>, </xsl:text>
                                    </xsl:if>
                                </xsl:for-each>
                            </td>
                        </tr>
                    </table>
                    <hr color="#EEEEEE"/>
                    <a href="#top" style="font-size: 0.9em">Back to top</a><br/><br/>
                </xsl:if>
            </xsl:if>
        </xsl:for-each>
    </xsl:for-each>
</xsl:template>

<xsl:template name="callback">
    <xsl:variable name="url">dxpprocess://<xsl:value-of select="CpCommand/CommandName"/>?<xsl:value-of select="CpCommand/Parameters"/></xsl:variable>

    <xsl:attribute name="href"><xsl:value-of select="$url"/></xsl:attribute>
    <xsl:attribute name="class">callback</xsl:attribute>
    <acronym>
        <xsl:attribute name="title"><xsl:value-of select="$url"/></xsl:attribute>
        <xsl:value-of select="Name"/>
    </acronym>
</xsl:template>

<xsl:template name="apply_column_index_attribute">
    <xsl:param name="index"><xsl:value-of select="position()"/></xsl:param>

    <xsl:attribute name="class">
        <xsl:value-of select="concat('column', $index)"/>
    </xsl:attribute>
</xsl:template>

<xsl:template name="classify_row_even_or_odd">
    <xsl:param name="row_offset">0</xsl:param>

    <xsl:choose>
        <xsl:when test="(position() + $row_offset) mod 2 = 0">
            <xsl:attribute name="class">onmouseout_even</xsl:attribute>
            <xsl:attribute name="onmouseover">className = 'onmouseover_even'</xsl:attribute>
            <xsl:attribute name="onmouseout">className = 'onmouseout_even'</xsl:attribute>
        </xsl:when>
        <xsl:otherwise>
            <xsl:attribute name="class">onmouseout_odd</xsl:attribute>
            <xsl:attribute name="onmouseover">className = 'onmouseover_odd'</xsl:attribute>
            <xsl:attribute name="onmouseout">className = 'onmouseout_odd'</xsl:attribute>
        </xsl:otherwise>
    </xsl:choose>
</xsl:template>

<xsl:template match="Filename">
    <xsl:element name="a">
        <xsl:attribute name="href">file:///<xsl:value-of select="."/></xsl:attribute>
        <xsl:attribute name="class">file</xsl:attribute>
        <acronym>
            <xsl:attribute name="title"><xsl:value-of select="."/></xsl:attribute>
            <xsl:apply-templates select="text()|*"/>
        </acronym>
    </xsl:element>
</xsl:template>

</xsl:stylesheet>
