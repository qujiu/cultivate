<GameFile>
  <PropertyGroup Name="anI_taideng" Type="Node" ID="3779b462-6cf4-4d47-91b5-366bdfb1f5b3" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="40" Speed="1.0000" ActivedAnimationName="ani_hit">
        <Timeline ActionTag="-878741141" Property="Position">
          <PointFrame FrameIndex="0" X="0.0000" Y="77.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="20" X="0.0000" Y="77.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="35" X="0.0000" Y="77.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="40" X="0.0000" Y="77.0000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="-878741141" Property="Scale">
          <ScaleFrame FrameIndex="0" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="20" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="35" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="40" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-878741141" Property="RotationSkew">
          <ScaleFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="20" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="35" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="40" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-878741141" Property="VisibleForFrame">
          <BoolFrame FrameIndex="20" Tween="False" Value="False" />
          <BoolFrame FrameIndex="35" Tween="False" Value="True" />
          <BoolFrame FrameIndex="40" Tween="False" Value="True" />
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="ani_touch" StartIndex="0" EndIndex="20">
          <RenderColor A="150" R="248" G="248" B="255" />
        </AnimationInfo>
        <AnimationInfo Name="ani_hit" StartIndex="20" EndIndex="40">
          <RenderColor A="150" R="135" G="206" B="235" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Node" Tag="104" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="Image_3" ActionTag="-878741141" Tag="107" IconVisible="False" LeftMargin="-92.5000" RightMargin="-92.5000" TopMargin="-177.0000" BottomMargin="-23.0000" LeftEage="61" RightEage="61" TopEage="66" BottomEage="66" Scale9OriginX="61" Scale9OriginY="66" Scale9Width="63" Scale9Height="68" ctype="ImageViewObjectData">
            <Size X="185.0000" Y="200.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position Y="77.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="ui/woshi/taideng_03.png" Plist="" />
          </AbstractNodeData>
          <AbstractNodeData Name="Image_1" ActionTag="1305433791" Tag="105" IconVisible="False" LeftMargin="-72.0000" RightMargin="-72.0000" TopMargin="-179.0000" BottomMargin="61.0000" LeftEage="47" RightEage="47" TopEage="38" BottomEage="38" Scale9OriginX="47" Scale9OriginY="38" Scale9Width="50" Scale9Height="42" ctype="ImageViewObjectData">
            <Size X="144.0000" Y="118.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position Y="120.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="ui/woshi/taideng_01.png" Plist="" />
          </AbstractNodeData>
          <AbstractNodeData Name="Image_2" ActionTag="2099966903" Tag="106" IconVisible="False" LeftMargin="-74.0000" RightMargin="-74.0000" TopMargin="-67.5000" BottomMargin="-67.5000" LeftEage="48" RightEage="48" TopEage="44" BottomEage="44" Scale9OriginX="48" Scale9OriginY="44" Scale9Width="52" Scale9Height="47" ctype="ImageViewObjectData">
            <Size X="148.0000" Y="135.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="ui/woshi/taideng_02.png" Plist="" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>