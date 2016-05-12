<GameFile>
  <PropertyGroup Name="Character" Type="Node" ID="87ba9357-52c7-4ed1-a12f-6d5d33c20404" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="5" Speed="0.1667" ActivedAnimationName="chop">
        <Timeline ActionTag="-1532555727" Property="FileData">
          <TextureFrame FrameIndex="0" Tween="False">
            <TextureFile Type="Normal" Path="character1.png" Plist="" />
          </TextureFrame>
          <TextureFrame FrameIndex="1" Tween="False">
            <TextureFile Type="Normal" Path="character1.png" Plist="" />
          </TextureFrame>
          <TextureFrame FrameIndex="2" Tween="False">
            <TextureFile Type="Normal" Path="Assets 2/Images/resources-2x/character2.png" Plist="" />
          </TextureFrame>
          <TextureFrame FrameIndex="3" Tween="False">
            <TextureFile Type="Normal" Path="Assets 2/Images/resources-2x/character3.png" Plist="" />
          </TextureFrame>
          <TextureFrame FrameIndex="4" Tween="False">
            <TextureFile Type="Normal" Path="Assets 2/Images/resources-2x/character3.png" Plist="" />
          </TextureFrame>
          <TextureFrame FrameIndex="5" Tween="False">
            <TextureFile Type="Normal" Path="character1.png" Plist="" />
          </TextureFrame>
        </Timeline>
        <Timeline ActionTag="-1532555727" Property="BlendFunc">
          <BlendFuncFrame FrameIndex="0" Tween="False" Src="1" Dst="771" />
          <BlendFuncFrame FrameIndex="1" Tween="False" Src="1" Dst="771" />
          <BlendFuncFrame FrameIndex="2" Tween="False" Src="1" Dst="771" />
          <BlendFuncFrame FrameIndex="3" Tween="False" Src="1" Dst="771" />
          <BlendFuncFrame FrameIndex="4" Tween="False" Src="1" Dst="771" />
          <BlendFuncFrame FrameIndex="5" Tween="False" Src="1" Dst="771" />
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="default" StartIndex="0" EndIndex="0">
          <RenderColor A="150" R="240" G="255" B="240" />
        </AnimationInfo>
        <AnimationInfo Name="chop" StartIndex="1" EndIndex="6">
          <RenderColor A="150" R="124" G="252" B="0" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Node" CustomClassName="Character" Tag="3" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="Cat" ActionTag="-1532555727" Tag="4" IconVisible="False" LeftMargin="-365.0000" TopMargin="-217.0000" ctype="SpriteObjectData">
            <Size X="365.0000" Y="217.0000" />
            <AnchorPoint ScaleX="1.0000" />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="Assets 2/Images/resources-2x/character3.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>