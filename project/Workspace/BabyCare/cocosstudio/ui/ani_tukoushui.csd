<GameFile>
  <PropertyGroup Name="ani_tukoushui" Type="Node" ID="43475158-e7cb-456e-a473-1a480b2356a9" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="75" Speed="1.0000" ActivedAnimationName="ani_hit">
        <Timeline ActionTag="-10867981" Property="Position">
          <PointFrame FrameIndex="30" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="50" X="0.0000" Y="-50.0000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="-10867981" Property="FileData">
          <TextureFrame FrameIndex="0" Tween="False">
            <TextureFile Type="Normal" Path="ui/yushi/ani_koushui_01.png" Plist="" />
          </TextureFrame>
          <TextureFrame FrameIndex="15" Tween="False">
            <TextureFile Type="Normal" Path="ui/yushi/ani_koushui_01.png" Plist="" />
          </TextureFrame>
          <TextureFrame FrameIndex="30" Tween="False">
            <TextureFile Type="Normal" Path="ui/yushi/ani_koushui_02.png" Plist="" />
          </TextureFrame>
          <TextureFrame FrameIndex="50" Tween="False">
            <TextureFile Type="Normal" Path="ui/yushi/ani_koushui_03.png" Plist="" />
          </TextureFrame>
          <TextureFrame FrameIndex="75" Tween="False">
            <TextureFile Type="Normal" Path="ui/yushi/ani_koushui_03.png" Plist="" />
          </TextureFrame>
        </Timeline>
        <Timeline ActionTag="-10867981" Property="BlendFunc">
          <BlendFuncFrame FrameIndex="0" Tween="False" Src="1" Dst="771" />
          <BlendFuncFrame FrameIndex="15" Tween="False" Src="1" Dst="771" />
          <BlendFuncFrame FrameIndex="30" Tween="False" Src="1" Dst="771" />
          <BlendFuncFrame FrameIndex="50" Tween="False" Src="1" Dst="771" />
          <BlendFuncFrame FrameIndex="75" Tween="False" Src="1" Dst="771" />
        </Timeline>
        <Timeline ActionTag="-10867981" Property="FrameEvent">
          <EventFrame FrameIndex="75" Tween="False" Value="onFrameEvent" />
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="ani_touch" StartIndex="0" EndIndex="15">
          <RenderColor A="255" R="224" G="255" B="255" />
        </AnimationInfo>
        <AnimationInfo Name="ani_hit" StartIndex="15" EndIndex="80">
          <RenderColor A="255" R="255" G="140" B="0" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Node" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="koushui" ActionTag="-10867981" Tag="3" FrameEvent="onFrameEvent" IconVisible="False" LeftMargin="-227.5000" RightMargin="-227.5000" TopMargin="-233.5000" BottomMargin="-333.5000" ctype="SpriteObjectData">
            <Size X="455.0000" Y="567.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position Y="-50.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="ui/yushi/ani_koushui_03.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>