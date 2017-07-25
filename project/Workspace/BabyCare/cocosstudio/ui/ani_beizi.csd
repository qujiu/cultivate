<GameFile>
  <PropertyGroup Name="ani_beizi" Type="Node" ID="7ea9b7c3-2fc6-4806-9672-9c10253e2880" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="115" Speed="1.0000" ActivedAnimationName="beizi_hit">
        <Timeline ActionTag="777888358" Property="Position">
          <PointFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="15" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="777888358" Property="Scale">
          <ScaleFrame FrameIndex="0" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="15" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="777888358" Property="RotationSkew">
          <ScaleFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="15" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="777888358" Property="FileData">
          <TextureFrame FrameIndex="0" Tween="False">
            <TextureFile Type="Normal" Path="ui/yushi/ani_item_koubei_xiao.png" Plist="" />
          </TextureFrame>
          <TextureFrame FrameIndex="15" Tween="False">
            <TextureFile Type="Normal" Path="ui/yushi/ani_item_koubei_xiao.png" Plist="" />
          </TextureFrame>
          <TextureFrame FrameIndex="35" Tween="False">
            <TextureFile Type="Normal" Path="ui/yushi/ani_item_koubei_heshui_1.png" Plist="" />
          </TextureFrame>
          <TextureFrame FrameIndex="55" Tween="False">
            <TextureFile Type="Normal" Path="ui/yushi/ani_item_koubei_heshui_2.png" Plist="" />
          </TextureFrame>
          <TextureFrame FrameIndex="75" Tween="False">
            <TextureFile Type="Normal" Path="ui/yushi/ani_item_koubei_heshui_3.png" Plist="" />
          </TextureFrame>
          <TextureFrame FrameIndex="95" Tween="False">
            <TextureFile Type="Normal" Path="ui/yushi/ani_item_koubei.png" Plist="" />
          </TextureFrame>
          <TextureFrame FrameIndex="115" Tween="False">
            <TextureFile Type="Normal" Path="ui/yushi/ani_item_koubei.png" Plist="" />
          </TextureFrame>
        </Timeline>
        <Timeline ActionTag="777888358" Property="BlendFunc">
          <BlendFuncFrame FrameIndex="0" Tween="False" Src="1" Dst="771" />
          <BlendFuncFrame FrameIndex="15" Tween="False" Src="1" Dst="771" />
          <BlendFuncFrame FrameIndex="35" Tween="False" Src="1" Dst="771" />
          <BlendFuncFrame FrameIndex="55" Tween="False" Src="1" Dst="771" />
          <BlendFuncFrame FrameIndex="75" Tween="False" Src="1" Dst="771" />
          <BlendFuncFrame FrameIndex="95" Tween="False" Src="1" Dst="771" />
          <BlendFuncFrame FrameIndex="115" Tween="False" Src="1" Dst="771" />
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="beizi_touch" StartIndex="0" EndIndex="15">
          <RenderColor A="255" R="221" G="160" B="221" />
        </AnimationInfo>
        <AnimationInfo Name="beizi_hit" StartIndex="15" EndIndex="115">
          <RenderColor A="255" R="65" G="105" B="225" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Node" Tag="136" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="Sprite1" ActionTag="777888358" Tag="137" IconVisible="False" LeftMargin="-64.0000" RightMargin="-64.0000" TopMargin="-45.0000" BottomMargin="-45.0000" ctype="SpriteObjectData">
            <Size X="128.0000" Y="90.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="ui/yushi/ani_item_koubei_heshui_1.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>