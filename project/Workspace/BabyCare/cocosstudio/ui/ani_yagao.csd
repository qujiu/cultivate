<GameFile>
  <PropertyGroup Name="ani_yagao" Type="Node" ID="f22c765c-9bdb-450f-b85b-9930a0935da2" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="120" Speed="1.0000" ActivedAnimationName="ani_touch">
        <Timeline ActionTag="-1661124889" Property="Position">
          <PointFrame FrameIndex="30" X="-86.9600" Y="-63.9000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="-1661124889" Property="VisibleForFrame">
          <BoolFrame FrameIndex="0" Tween="False" Value="False" />
          <BoolFrame FrameIndex="30" Tween="False" Value="True" />
          <BoolFrame FrameIndex="70" Tween="False" Value="True" />
          <BoolFrame FrameIndex="115" Tween="False" Value="True" />
          <BoolFrame FrameIndex="120" Tween="False" Value="False" />
        </Timeline>
        <Timeline ActionTag="1260375865" Property="Position">
          <PointFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="10" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="60" X="25.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="70" X="30.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="1260375865" Property="Scale">
          <ScaleFrame FrameIndex="0" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="10" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="60" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="1260375865" Property="RotationSkew">
          <ScaleFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="10" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="60" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="76" X="30.0000" Y="30.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="115" X="100.0000" Y="100.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="1260375865" Property="FileData">
          <TextureFrame FrameIndex="15" Tween="False">
            <TextureFile Type="Normal" Path="ui/yushi/ani_item_YaGao_2.png" Plist="" />
          </TextureFrame>
          <TextureFrame FrameIndex="30" Tween="False">
            <TextureFile Type="Normal" Path="ui/yushi/ani_item_YaGao_2_1.png" Plist="" />
          </TextureFrame>
          <TextureFrame FrameIndex="60" Tween="False">
            <TextureFile Type="Normal" Path="ui/yushi/ani_item_YaGao_2_1.png" Plist="" />
          </TextureFrame>
          <TextureFrame FrameIndex="70" Tween="False">
            <TextureFile Type="Normal" Path="ui/yushi/ani_item_YaGao_2_1.png" Plist="" />
          </TextureFrame>
          <TextureFrame FrameIndex="76" Tween="False">
            <TextureFile Type="Normal" Path="ui/yushi/ani_item_YaGao_2.png" Plist="" />
          </TextureFrame>
          <TextureFrame FrameIndex="115" Tween="False">
            <TextureFile Type="Normal" Path="ui/yushi/ani_item_YaGao_2.png" Plist="" />
          </TextureFrame>
        </Timeline>
        <Timeline ActionTag="1260375865" Property="BlendFunc">
          <BlendFuncFrame FrameIndex="15" Tween="False" Src="1" Dst="771" />
          <BlendFuncFrame FrameIndex="30" Tween="False" Src="1" Dst="771" />
          <BlendFuncFrame FrameIndex="60" Tween="False" Src="1" Dst="771" />
          <BlendFuncFrame FrameIndex="70" Tween="False" Src="1" Dst="771" />
          <BlendFuncFrame FrameIndex="76" Tween="False" Src="1" Dst="771" />
          <BlendFuncFrame FrameIndex="115" Tween="False" Src="1" Dst="771" />
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="ani_touch" StartIndex="0" EndIndex="10">
          <RenderColor A="255" R="255" G="165" B="0" />
        </AnimationInfo>
        <AnimationInfo Name="ani_hit" StartIndex="15" EndIndex="120">
          <RenderColor A="255" R="64" G="224" B="208" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Node" Tag="558" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="Img_yeti" ActionTag="-1661124889" VisibleForFrame="False" Tag="560" IconVisible="False" LeftMargin="-101.9600" RightMargin="71.9600" TopMargin="58.9000" BottomMargin="-68.9000" LeftEage="9" RightEage="9" TopEage="3" BottomEage="3" Scale9OriginX="9" Scale9OriginY="3" Scale9Width="12" Scale9Height="4" ctype="ImageViewObjectData">
            <Size X="30.0000" Y="10.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="-86.9600" Y="-63.9000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="ui/yushi/ani_item_YaGao_3.png" Plist="" />
          </AbstractNodeData>
          <AbstractNodeData Name="Ima_yagao" ActionTag="1260375865" Tag="561" IconVisible="False" LeftMargin="-101.5000" RightMargin="-101.5000" TopMargin="-74.5000" BottomMargin="-74.5000" ctype="SpriteObjectData">
            <Size X="203.0000" Y="149.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="ui/yushi/ani_item_YaGao_2.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>