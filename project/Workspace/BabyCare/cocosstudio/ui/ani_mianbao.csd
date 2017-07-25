<GameFile>
  <PropertyGroup Name="ani_mianbao" Type="Node" ID="515d0169-f0a7-4a36-a6ee-81a626d6644a" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="85" Speed="1.0000" ActivedAnimationName="ani_hit">
        <Timeline ActionTag="-1195947813" Property="Position">
          <PointFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="15" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="20" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="25" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="65" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="85" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="-1195947813" Property="Scale">
          <ScaleFrame FrameIndex="0" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="15" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="20" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="25" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="65" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="85" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-1195947813" Property="RotationSkew">
          <ScaleFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="15" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="20" X="-5.0000" Y="-5.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="25" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="65" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="85" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-1195947813" Property="FileData">
          <TextureFrame FrameIndex="0" Tween="False">
            <TextureFile Type="Normal" Path="ui/canzhuo/canting_mianbao_01.png" Plist="" />
          </TextureFrame>
          <TextureFrame FrameIndex="15" Tween="False">
            <TextureFile Type="Normal" Path="ui/canzhuo/canting_mianbao_01.png" Plist="" />
          </TextureFrame>
          <TextureFrame FrameIndex="45" Tween="False">
            <TextureFile Type="Normal" Path="ui/canzhuo/canting_mianbao_02.png" Plist="" />
          </TextureFrame>
          <TextureFrame FrameIndex="65" Tween="False">
            <TextureFile Type="Normal" Path="ui/canzhuo/canting_mianbao_03.png" Plist="" />
          </TextureFrame>
          <TextureFrame FrameIndex="85" Tween="False">
            <TextureFile Type="Normal" Path="ui/canzhuo/canting_mianbao_03.png" Plist="" />
          </TextureFrame>
        </Timeline>
        <Timeline ActionTag="-1195947813" Property="BlendFunc">
          <BlendFuncFrame FrameIndex="0" Tween="False" Src="1" Dst="771" />
          <BlendFuncFrame FrameIndex="15" Tween="False" Src="1" Dst="771" />
          <BlendFuncFrame FrameIndex="45" Tween="False" Src="1" Dst="771" />
          <BlendFuncFrame FrameIndex="65" Tween="False" Src="1" Dst="771" />
          <BlendFuncFrame FrameIndex="85" Tween="False" Src="1" Dst="771" />
        </Timeline>
        <Timeline ActionTag="-1195947813" Property="VisibleForFrame">
          <BoolFrame FrameIndex="80" Tween="False" Value="True" />
          <BoolFrame FrameIndex="85" Tween="False" Value="False" />
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="ani_touch" StartIndex="0" EndIndex="15">
          <RenderColor A="255" R="72" G="209" B="204" />
        </AnimationInfo>
        <AnimationInfo Name="ani_trigger" StartIndex="15" EndIndex="20">
          <RenderColor A="255" R="100" G="149" B="237" />
        </AnimationInfo>
        <AnimationInfo Name="ani_hit" StartIndex="25" EndIndex="85">
          <RenderColor A="255" R="152" G="251" B="152" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Node" Tag="36" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="mianbao" ActionTag="-1195947813" VisibleForFrame="False" Tag="53" IconVisible="False" LeftMargin="-67.5000" RightMargin="-67.5000" TopMargin="-41.0000" BottomMargin="-41.0000" ctype="SpriteObjectData">
            <Size X="135.0000" Y="82.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="ui/canzhuo/canting_mianbao_03.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>