<GameFile>
  <PropertyGroup Name="ani_daqi" Type="Node" ID="81020f9f-b6f8-4b66-9b93-d2fa74515eb8" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="60" Speed="1.0000">
        <Timeline ActionTag="1007187621" Property="FileData">
          <TextureFrame FrameIndex="0" Tween="False">
            <TextureFile Type="Normal" Path="ui/toy/ani_item_QiGuan_01.png" Plist="" />
          </TextureFrame>
          <TextureFrame FrameIndex="20" Tween="False">
            <TextureFile Type="Normal" Path="ui/toy/ani_item_QiGuan_01.png" Plist="" />
          </TextureFrame>
          <TextureFrame FrameIndex="40" Tween="False">
            <TextureFile Type="Normal" Path="ui/toy/ani_item_QiGuan_02.png" Plist="" />
          </TextureFrame>
          <TextureFrame FrameIndex="60" Tween="False">
            <TextureFile Type="Normal" Path="ui/toy/ani_item_QiGuan_01.png" Plist="" />
          </TextureFrame>
        </Timeline>
        <Timeline ActionTag="1007187621" Property="BlendFunc">
          <BlendFuncFrame FrameIndex="0" Tween="False" Src="1" Dst="771" />
          <BlendFuncFrame FrameIndex="20" Tween="False" Src="1" Dst="771" />
          <BlendFuncFrame FrameIndex="40" Tween="False" Src="1" Dst="771" />
          <BlendFuncFrame FrameIndex="60" Tween="False" Src="1" Dst="771" />
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="ani_touch" StartIndex="0" EndIndex="20">
          <RenderColor A="255" R="184" G="134" B="11" />
        </AnimationInfo>
        <AnimationInfo Name="ani_hit" StartIndex="20" EndIndex="40">
          <RenderColor A="255" R="46" G="139" B="87" />
        </AnimationInfo>
        <AnimationInfo Name="ani_release" StartIndex="40" EndIndex="60">
          <RenderColor A="255" R="0" G="100" B="0" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Node" Tag="95" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="Image1" ActionTag="1007187621" Tag="96" IconVisible="False" LeftMargin="-99.5000" RightMargin="-99.5000" TopMargin="-59.5000" BottomMargin="-59.5000" ctype="SpriteObjectData">
            <Size X="199.0000" Y="119.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="ui/toy/ani_item_QiGuan_01.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>