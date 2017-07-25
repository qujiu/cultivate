<GameFile>
  <PropertyGroup Name="Ani_Yuhua" Type="Node" ID="84c57cca-56a4-4a56-98b3-a917fae97c81" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="15" Speed="2.0000" ActivedAnimationName="yuhua_release">
        <Timeline ActionTag="-552585952" Property="Position">
          <PointFrame FrameIndex="0" X="-1.2988" Y="2.6019">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="10" X="-1.2988" Y="2.6019">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="-552585952" Property="Scale">
          <ScaleFrame FrameIndex="0" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="10" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-552585952" Property="RotationSkew">
          <ScaleFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="10" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-552585952" Property="VisibleForFrame">
          <BoolFrame FrameIndex="0" Tween="False" Value="True" />
          <BoolFrame FrameIndex="10" Tween="False" Value="False" />
        </Timeline>
        <Timeline ActionTag="1267831909" Property="Position">
          <PointFrame FrameIndex="0" X="0.0000" Y="19.0011">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="5" X="0.0000" Y="19.0011">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="10" X="0.0000" Y="19.0011">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="15" X="0.0000" Y="19.0011">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="1267831909" Property="Scale">
          <ScaleFrame FrameIndex="0" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="5" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="10" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="15" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="1267831909" Property="RotationSkew">
          <ScaleFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="5" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="10" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="15" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="1267831909" Property="VisibleForFrame">
          <BoolFrame FrameIndex="10" Tween="False" Value="True" />
          <BoolFrame FrameIndex="15" Tween="False" Value="True" />
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="yuhua_touch" StartIndex="0" EndIndex="5">
          <RenderColor A="255" R="245" G="255" B="250" />
        </AnimationInfo>
        <AnimationInfo Name="yuhua_release" StartIndex="10" EndIndex="15">
          <RenderColor A="255" R="124" G="252" B="0" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Node" Tag="168" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="Particle_1" ActionTag="-552585952" Tag="170" IconVisible="True" LeftMargin="-1.2988" RightMargin="1.2988" TopMargin="-2.6019" BottomMargin="2.6019" ctype="ParticleObjectData">
            <Size X="0.0000" Y="0.0000" />
            <AnchorPoint />
            <Position X="-1.2988" Y="2.6019" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="Particles/effect_xizao_paomo.plist" Plist="" />
            <BlendFunc Src="772" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="Image_1" ActionTag="1267831909" Tag="169" IconVisible="False" LeftMargin="-54.0000" RightMargin="-54.0000" TopMargin="-75.0011" BottomMargin="-36.9989" LeftEage="35" RightEage="35" TopEage="36" BottomEage="36" Scale9OriginX="35" Scale9OriginY="36" Scale9Width="38" Scale9Height="40" ctype="ImageViewObjectData">
            <Size X="108.0000" Y="112.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position Y="19.0011" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="ui/yushi/ui_prop_flowerbath.png" Plist="" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>