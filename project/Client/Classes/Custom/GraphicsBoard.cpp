#include "GraphicsBoard.h"

GraphicsBoard::GraphicsBoard() :
native_sprite_(NULL),
brush_sprite_(NULL),
render_texture_(NULL),
clear_alpha_(1.0f),
use_shader_mode_(EGraphicsBoardMode_Null),
clear_duration_(.5f)
{
}

GraphicsBoard::~GraphicsBoard()
{
	if (_scheduler->isScheduled(schedule_selector(GraphicsBoard::BrushMoveIntelligentUpdate), this))
	{
		this->unschedule(schedule_selector(GraphicsBoard::BrushMoveIntelligentUpdate));
	}
	native_sprite_->removeFromParent();
	brush_sprite_->release();
	render_texture_->release();
}

bool GraphicsBoard::InitWithFile(const Rect& rect, const char* graphics_file_path, const Color4B& color)
{
	auto rt = RenderTexture::create(rect.size.width, rect.size.height, Texture2D::PixelFormat::RGBA8888);
	rt->clear(0, 0, 0, 1);
	native_sprite_ = Sprite::createWithTexture(rt->getSprite()->getTexture());
	auto brush_sprite = Sprite::create(graphics_file_path);
	return InitWithFile(native_sprite_, brush_sprite, EGraphicsBoardMode_Color, color);
}

bool GraphicsBoard::InitWithFile(const char* native_file_path, const char* graphics_file_path, const EGraphicsBoardMode& mode, const Color4B& color, const bool bFlippedX)
{
	native_sprite_ = Sprite::create(native_file_path);
	auto brush_sprite = Sprite::create(graphics_file_path);
	return InitWithFile(native_sprite_, brush_sprite, mode, color, bFlippedX);
}

bool GraphicsBoard::InitWithFile(Sprite* native, Sprite* graphics, const EGraphicsBoardMode& mode, const Color4B& color, const bool bFlippedX)
{
	do
	{
		use_shader_mode_ = mode;
		native_sprite_ = native;
		CC_BREAK_IF(!native_sprite_);
		addChild(native_sprite_);
		BlendFunc blend_func = { GL_ONE, GL_ONE_MINUS_SRC_ALPHA };
		native_sprite_->setBlendFunc(blend_func);
		//native_sprite_->setFlippedX(bFlippedX);

		auto brush_sprite = graphics;
		brush_sprite->setAnchorPoint(Vec2(0.5f, 0.5f));
		brush_sprite->setPosition(Vec2(0, 0));
		SetBrush(brush_sprite, color);

		auto size = native_sprite_->getContentSize();

		render_texture_ = RenderTexture::create(size.width, size.height, Texture2D::PixelFormat::RGBA8888);
		render_texture_->retain();
		render_texture_->clear(0, 0, 0, 0);
		/*BlendFunc blend_func = { GL_ONE, GL_ONE_MINUS_SRC_ALPHA };
		render_texture_->getSprite()->setBlendFunc(blend_func);*/
		//this->addChild(render_texture_);


		SetShader(mode);
		//SetMode(mode);

		return true;
	} while (0);
	return false;
}

void GraphicsBoard::listenBackToForeground(Object *obj)
{
	SetShader(use_shader_mode_);
}

void GraphicsBoard::listenEnterToBackground(Object *obj)
{
}

RenderTexture* GraphicsBoard::render_texture()
{
	return render_texture_;
}

Sprite* GraphicsBoard::native_sprite()
{
	return native_sprite_;
}

Sprite* GraphicsBoard::graphics_sprite()
{
	return brush_sprite_;
}

const Size& GraphicsBoard::graphics_board_size() const
{
	CC_ASSERT(render_texture_);
	return render_texture_->getSprite()->getContentSize();
}

void GraphicsBoard::CopyFrom(const GraphicsBoard* temple)
{
	if (native_sprite_)
	{
		native_sprite_->setTexture(temple->native_sprite_->getTexture());
	}
	else
	{
		native_sprite_ = Sprite::createWithTexture(temple->native_sprite_->getTexture());
		addChild(native_sprite_);
		BlendFunc blend_func = { GL_ONE, GL_ONE_MINUS_SRC_ALPHA };
		native_sprite_->setBlendFunc(blend_func);
	}
	if (brush_sprite_)
	{
		brush_sprite_->setTexture(temple->brush_sprite_->getTexture());
	}
	else
	{
		auto brush_sprite = Sprite::createWithTexture(temple->brush_sprite_->getTexture());
		brush_sprite->setAnchorPoint(Vec2(0.5f, 0.5f));
		brush_sprite->setPosition(Vec2(0, 0));
		SetBrush(brush_sprite);
	}
	auto size = native_sprite_->getContentSize();
	if (!render_texture_)
	{
		render_texture_ = RenderTexture::create(size.width, size.height, Texture2D::PixelFormat::RGBA8888);
		render_texture_->retain();
		//render_texture_->clear(0, 0, 0, 0);
	}
	ClearRenderTexture();
	native_sprite_->setAnchorPoint(temple->native_sprite_->getAnchorPoint());
	render_texture_->begin();
	auto sprite = Sprite::createWithTexture(temple->render_texture_->getSprite()->getTexture());
	sprite->setPosition(size*.5f);
	sprite->setFlipY(true);
	sprite->visit();
	render_texture_->end();
	use_shader_mode_ = temple->use_shader_mode_;
	SetShader(use_shader_mode_);
}

void GraphicsBoard::SetShader(const EGraphicsBoardMode& mode)
{
	std::string vs, fs;
	switch (mode)
	{
	case EGraphicsBoardMode_Color:
		vs = "res/Shaders/GraphicsBoard_Color.vsh";
		fs = "res/Shaders/GraphicsBoard_Color.fsh";
		break;
	case EGraphicsBoardMode_EraserWithPalette:
		vs = "res/Shaders/GraphicsBoard_EraserWithPalette.vsh";
		fs = "res/Shaders/GraphicsBoard_EraserWithPalette.fsh";
		break;
	case EGraphicsBoardMode_ColorWithPalette:
		vs = "res/Shaders/GraphicsBoard_ColorWithPalette.vsh";
		fs = "res/Shaders/GraphicsBoard_ColorWithPalette.fsh";
		break;
	case EGraphicsBoardMode_ColorWithStencil:
		vs = "res/Shaders/GraphicsBoard_ColorWithStencil.vsh";
		fs = "res/Shaders/GraphicsBoard_ColorWithStencil.fsh";
		break;
	case EGraphicsBoardMode_Stencil:
		vs = "res/Shaders/GraphicsBoard_Stencil.vsh";
		fs = "res/Shaders/GraphicsBoard_Stencil.fsh";
		break;
	}
	auto glprogram = GLProgram::createWithFilenames(vs, fs);
	auto glprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);
	native_sprite_->setGLProgramState(glprogramstate);
	CHECK_GL_ERROR_DEBUG();
	glprogramstate->setUniformTexture("u_texture1", render_texture_->getSprite()->getTexture());
	CHECK_GL_ERROR_DEBUG();
}

//void GraphicsBoard::SetMode(const EGraphicsBoardMode& mode)
//{
//	auto glprogramstate = native_sprite_->getGLProgramState();
//	glprogramstate->setUniformInt("u_mode", mode);
//	CHECK_GL_ERROR_DEBUG();
//}

void GraphicsBoard::SetBrush(Sprite* brush, const Color4B& color)
{
	if (brush)
	{
		if (brush_sprite_)
		{
			brush_sprite_->release();
		}
		brush_sprite_ = brush;
		brush_sprite_->retain();
	}
	BlendFunc blend_func = { GL_ONE, GL_ONE_MINUS_SRC_ALPHA };
	brush_sprite_->setBlendFunc(blend_func);
	brush_sprite_->setColor(ccc3(color.r, color.g, color.b));
	brush_sprite_->setOpacity(color.a);
}

void GraphicsBoard::SetEraser(Sprite* eraser, bool is_show_palette)
{
	if (eraser)
	{
		if (brush_sprite_)
		{
			brush_sprite_->release();
		}
		brush_sprite_ = eraser;
		brush_sprite_->retain();
	}
	BlendFunc blend_func = { GL_ZERO, GL_ONE_MINUS_SRC_ALPHA };
	brush_sprite_->setBlendFunc(blend_func);
	if (is_show_palette)
	{
		render_texture_->clear(0, 0, 0, 1);
	}
}

void GraphicsBoard::BrushClick(const Vec2& pos)
{
	CC_ASSERT(render_texture_);
	CC_ASSERT(brush_sprite_);

	Vec2 nodePos = this->getPosition();
	cocos2d::Size size = render_texture_->getSprite()->getContentSize();
	//cocos2d::Rect rect(nodePos.x, nodePos.y, size.width, size.height);

	render_texture_->begin();
	renderBrushBefore();
	//if (rect.containsPoint(pos))
	{
		auto sprite = Sprite::createWithTexture(brush_sprite_->getTexture());
		sprite->setColor(brush_sprite_->getColor());
		sprite->setOpacity(brush_sprite_->getOpacity());
		sprite->setBlendFunc(brush_sprite_->getBlendFunc());
		sprite->setScale(brush_sprite_->getScale());
		sprite->setFlipY(true);
		sprite->setPosition(Vec2(pos.x - nodePos.x, size.height - (pos.y - nodePos.y)));
		sprite->visit();
	}
	renderBrushAfter();
	render_texture_->end();
}

void GraphicsBoard::BrushMove(const Vec2& start, const Vec2& end)
{
	CC_ASSERT(render_texture_);
	CC_ASSERT(brush_sprite_);

	Vec2 nodePos = this->getPosition();
	cocos2d::Size size = render_texture_->getSprite()->getContentSize();
	//cocos2d::Rect rect(nodePos.x, nodePos.y, size.width, size.height);

	render_texture_->begin();
	renderBrushBefore();
	float distance = ccpDistance(start, end);
	if (distance > 1)
	{
		int d = distance;
		//int d = (int)distance >> 1;
		burshes_.clear();
		for (int i = 0; i < d; ++i)
		{
			auto sprite = Sprite::createWithTexture(brush_sprite_->getTexture());
			sprite->setColor(brush_sprite_->getColor());
			sprite->setOpacity(brush_sprite_->getOpacity());
			sprite->setBlendFunc(brush_sprite_->getBlendFunc());
			sprite->setScale(brush_sprite_->getScale());
			sprite->setFlipY(true);
			burshes_.push_back(sprite);
		}
		for (int i = 0; i < d; ++i)
		{
			float difx = end.x - start.x;
			float dify = end.y - start.y;
			float delta = (float)i / d;
			burshes_.at(i)->setPosition(Vec2((start.x - nodePos.x) + (difx * delta), size.height - (start.y + (dify * delta) - nodePos.y)));
			burshes_.at(i)->visit();
		}
	}
	renderBrushAfter();
	render_texture_->end();
}

#define _BRUSH_MOVE_MAX_DRAW_NUM_			200

void GraphicsBoard::BrushMoveIntelligent(const Vec2& start, const Vec2& end)
{
	CC_ASSERT(render_texture_);
	CC_ASSERT(brush_sprite_);

	Vec2 nodePos = this->getPosition();
	cocos2d::Size size = render_texture_->getSprite()->getContentSize();

	float distance = ccpDistance(start, end);
	if (distance < 1) return;
	if (brush_pos_array_.size() == (int)0 && distance <= _BRUSH_MOVE_MAX_DRAW_NUM_)
	{
		BrushMove(start, end);
	}
	else
	{
		float d = distance;
		Vec2 start_flag = start;
		while (d > _BRUSH_MOVE_MAX_DRAW_NUM_)
		{
			float difx = end.x - start_flag.x;
			float dify = end.y - start_flag.y;
			float delta_d = (float)_BRUSH_MOVE_MAX_DRAW_NUM_ / d;
			Vec4 data;
			data.x = start_flag.x;
			data.y = start_flag.y;
			data.z = start_flag.x + delta_d * difx;
			data.w = start_flag.y + delta_d * dify;
			brush_pos_array_.push_back(data);

			start_flag.x = data.z;
			start_flag.y = data.w;
			d -= _BRUSH_MOVE_MAX_DRAW_NUM_;
		}
		if (d > 0)
		{
			Vec4 data;
			data.x = start_flag.x;
			data.y = start_flag.y;
			data.z = end.x;
			data.w = end.y;
			brush_pos_array_.push_back(data);
		}
		if (!_scheduler->isScheduled(schedule_selector(GraphicsBoard::BrushMoveIntelligentUpdate), this))
		{
			this->schedule(schedule_selector(GraphicsBoard::BrushMoveIntelligentUpdate));
		}
	}
}

void GraphicsBoard::BrushMoveIntelligentUpdate(float delta)
{
	int size = brush_pos_array_.size();
	if (size > 0)
	{
		auto data = brush_pos_array_[0];
		BrushMove(Vec2(data.x, data.y), Vec2(data.z, data.w));
		brush_pos_array_.erase(brush_pos_array_.begin());
	}
}

bool GraphicsBoard::IsBrushIntelligentDone()
{
	int size = brush_pos_array_.size();
	return size == 0;
}

void GraphicsBoard::ClearRenderTexture()
{
	if (render_texture_)
	{
		render_texture_->clear(0, 0, 0, 0);
	}
}

void GraphicsBoard::ClearRenderTextureSlowly(float time)
{
	if (render_texture_)
	{
		this->schedule(schedule_selector(GraphicsBoard::ClearRenderScheduleCallback));
		clear_alpha_ = 1;
		clear_duration_ = time;
	}
}

void GraphicsBoard::ClearRenderScheduleCallback(float delta)
{
	if (render_texture_)
	{
		//clear_alpha_ -= delta * .5f;
		clear_alpha_ -= delta / clear_duration_;
		render_texture_->begin();
		cocos2d::Size size = render_texture_->getSprite()->getContentSize();
		DrawNode* draw = DrawNode::create();
		BlendFunc func = { GL_ZERO, GL_SRC_ALPHA };
		draw->setBlendFunc(func);
		Color4F color;
		color.r = 0;
		color.g = 0;
		color.b = 0;
		color.a = clear_alpha_;
		draw->drawDot(size * .5f, std::max(size.width, size.height) * .5f, color);
		draw->visit();
		render_texture_->end();
	}
	if (clear_alpha_ <= 0.0f)
	{
		this->unschedule(schedule_selector(GraphicsBoard::ClearRenderScheduleCallback));
		/*if (clear_callback_func_)
		{
		clear_callback_func_();
		}*/
	}
}

void GraphicsBoard::ReplaceDisplay(Sprite* dst)
{
	ClearRenderTexture();
	render_texture_->begin();
	cocos2d::Size size = render_texture_->getSprite()->getContentSize();
	/*sprite->setPosition(Vec2(pos.x, size.height - pos.y));
	sprite->setBlendFunc(brush_sprite_->getBlendFunc());*/

	BlendFunc func = { GL_ONE, GL_SRC_ALPHA };
	dst->setBlendFunc(func);
	//dst->setBlendFunc(brush_sprite_->getBlendFunc());
	dst->setAnchorPoint(Vec2(.5f, .5f));
	dst->setPosition(size.width * .5f, size.height * .5f);
	dst->visit();
	render_texture_->end();
}

void GraphicsBoard::renderBrushBefore()
{

}

void GraphicsBoard::renderBrush(Sprite* sprite, const Vec2& pos)
{
	cocos2d::Size size = render_texture_->getSprite()->getContentSize();
	sprite->setPosition(Vec2(pos.x, size.height - pos.y));
	sprite->setFlipY(true);
	sprite->visit();
}

void GraphicsBoard::renderBrushAfter()
{

}

void GraphicsBoard::SaveBlendTex()
{
	render_texture_->saveToFile("/cc.png");
}

void GraphicsBoard::setPosition(const Vec2& pos)
{
	Node::setPosition(pos);
	Vec2 world_pos = this->convertToWorldSpace(Vec2(0, 0));
	render_texture_->setPosition(ccpAdd(ccpMult(this->getContentSize(), .5f), world_pos));
}

void GraphicsBoard::setAnchorPoint(const Vec2& anchorPoint)
{
	Node::setAnchorPoint(anchorPoint);
	if (native_sprite_)
		native_sprite_->setAnchorPoint(anchorPoint);
}

GraphicsBoard* GraphicsBoard::Create(const Rect& rect, const char* graphics_file_path, const Color4B& color)
{
	auto node = new GraphicsBoard;
	if (node && node->InitWithFile(rect, graphics_file_path, color))
	{
		node->autorelease();
	}
	else
	{
		CC_SAFE_RELEASE(node);
	}
	return node;
}

GraphicsBoard* GraphicsBoard::Create(const char* native_file_path, const char* graphics_file_path, const EGraphicsBoardMode& mode, const Color4B& color, const bool bFlippedX)
{
	auto node = new GraphicsBoard;
	if (node && node->InitWithFile(native_file_path, graphics_file_path, mode, color, bFlippedX))
	{
		node->autorelease();
	}
	else
	{
		CC_SAFE_RELEASE(node);
	}
	return node;
}

GraphicsBoard* GraphicsBoard::Create()
{
	auto node = new GraphicsBoard;
	if (node)
	{
		node->autorelease();
	}
	else
	{
		CC_SAFE_RELEASE(node);
	}
	return node;
}

//
OverlayGraphicsBoard::OverlayGraphicsBoard() :current_native_file_path_("")
{
}

OverlayGraphicsBoard::~OverlayGraphicsBoard()
{
	for (int i = 0, cnt = graphics_boards_.size(); i < cnt; ++i)
	{
		auto graphics_board = graphics_boards_[i];
		graphics_board->removeFromParent();
	}
	graphics_boards_.clear();
	current_native_file_path_ = "";
}

void OverlayGraphicsBoard::CopyFrom(const OverlayGraphicsBoard* temple)
{
	if (!temple) return;
	ClearGraphicsBoards();
	for (int i = 0, cnt = temple->graphics_boards_.size(); i < cnt; ++i)
	{
		auto graphics_board = temple->graphics_boards_[i];
		auto copy = ChangeGraphicsBoardNull();
		copy->CopyFrom(graphics_board);
	}
	current_native_file_path_ = temple->current_native_file_path_;
}

bool OverlayGraphicsBoard::Init(const char* native_file_path, const char* graphics_file_path, const Color4B& color, const bool bFlippedX)
{
	//this->setAnchorPoint(ccp(.5f, .5f));
	ChangeGraphicsBoard(native_file_path, graphics_file_path, color, bFlippedX);

	return true;
}

bool OverlayGraphicsBoard::IsCurrentNative(const std::string& native_file_path)
{
	return native_file_path == current_native_file_path_;
}

GraphicsBoard* OverlayGraphicsBoard::ChangeGraphicsBoard(const char* native_file_path, const char* graphics_file_path, const Color4B& color, const bool bFlippedX)
{
	auto graphics_board = GraphicsBoard::Create(native_file_path, graphics_file_path, EGraphicsBoardMode_Stencil, color, bFlippedX);
	CC_ASSERT(graphics_board);
	addChild(graphics_board);
	//graphics_board->setAnchorPoint(ccp(.5f, .5f));
	//auto size = graphics_board->native_sprite()->getContentSize();
	graphics_boards_.push_back(graphics_board);
	current_native_file_path_ = native_file_path;
	return graphics_board;
}

GraphicsBoard* OverlayGraphicsBoard::ChangeGraphicsBoardNull()
{
	auto graphics_board = GraphicsBoard::Create();
	CC_ASSERT(graphics_board);
	addChild(graphics_board);
	//graphics_board->setAnchorPoint(ccp(.5f, .5f));
	graphics_boards_.push_back(graphics_board);
	return graphics_board;
}

void OverlayGraphicsBoard::ClearGraphicsBoards()
{
	for (int i = 0, cnt = graphics_boards_.size(); i < cnt; ++i)
	{
		auto graphics_board = graphics_boards_[i];
		//graphics_board->ClearRenderTexture();//? 
		graphics_board->removeFromParent();
	}
	graphics_boards_.clear();
	current_native_file_path_ = "";
}

void OverlayGraphicsBoard::ClearGraphicsBoardsSlowly()
{
	float dur = 1.2f;
	for (int i = 0, cnt = graphics_boards_.size(); i < cnt; ++i)
	{
		auto graphics_board = graphics_boards_[i];
		graphics_board->ClearRenderTextureSlowly(dur);
		//graphics_board->removeFromParent();
	}
	//graphics_boards_.clear();
	//current_native_file_path_ = "";

	auto action = DelayTime::create(1.3f);
	auto func = [&]()
	{
		for (int i = 0, cnt = graphics_boards_.size(); i < cnt; ++i)
		{
			auto graphics_board = graphics_boards_[i];
			graphics_board->removeFromParent();
		}
		graphics_boards_.clear();
		current_native_file_path_ = "";
	};
	runAction(Sequence::create(action, CallFunc::create(func), nullptr));
}

void OverlayGraphicsBoard::BrushClick(const Vec2& pos)
{
	auto size = graphics_boards_.size();
	if (size > 0)
	{
		auto graphics_board = graphics_boards_[size - 1];
		CC_ASSERT(graphics_board);
		auto size = graphics_board->native_sprite()->getContentSize();
		auto delta = ccp(getPositionX() - size.width * getAnchorPoint().x, getPositionY() - size.height * getAnchorPoint().y);
		graphics_board->BrushClick(pos - delta);
	}
}

void OverlayGraphicsBoard::BrushMove(const Vec2& start, const Vec2& end)
{
	auto size = graphics_boards_.size();
	if (size > 0)
	{
		auto graphics_board = graphics_boards_[size - 1];
		CC_ASSERT(graphics_board);
		auto size = graphics_board->native_sprite()->getContentSize();
		auto delta = ccp(getPositionX() - size.width * getAnchorPoint().x, getPositionY() - size.height * getAnchorPoint().y);
		graphics_board->BrushMove(start - delta, end - delta);
	}
}

void OverlayGraphicsBoard::EraserMove(const Vec2& start, const Vec2& end)
{
	auto size = graphics_boards_.size();
	GraphicsBoard* graphics_board_temp = NULL;
	if (size > 0)
	{
		graphics_board_temp = graphics_boards_[size - 1];
	}

	for (int i = 0; i < size - 1; ++i)
	{
		auto graphics_board = graphics_boards_[i];
		graphics_board->removeFromParent();
	}
	graphics_boards_.clear();
	graphics_boards_.push_back(graphics_board_temp);

	auto consize = graphics_board_temp->native_sprite()->getContentSize();
	auto delta = ccp(getPositionX() - consize.width * getAnchorPoint().x, getPositionY() - consize.height * getAnchorPoint().y);
	graphics_board_temp->BrushMove(start - delta, end - delta);
}

void OverlayGraphicsBoard::SetBrush(Sprite* brush, const Color4B& color)
{
	auto size = graphics_boards_.size();
	if (size > 0)
	{
		auto graphics_board = graphics_boards_[size - 1];
		CC_ASSERT(graphics_board);
		graphics_board->SetBrush(brush, color);
	}
}

void OverlayGraphicsBoard::SetEraser(Sprite* eraser, bool is_show_palette)
{
	auto size = graphics_boards_.size();
	if (size > 0)
	{
		auto graphics_board = graphics_boards_[size - 1];
		CC_ASSERT(graphics_board);
		graphics_board->SetEraser(eraser, is_show_palette);
	}
}

OverlayGraphicsBoard* OverlayGraphicsBoard::Create(const char* native_file_path, const char* graphics_file_path, const Color4B& color, const bool bFlippedX)
{
	OverlayGraphicsBoard* node = new OverlayGraphicsBoard();
	if (node && node->Init(native_file_path, graphics_file_path, color, bFlippedX))
	{
		node->autorelease();
	}
	else
	{
		CC_SAFE_RELEASE(node);
	}
	return node;
}

GraphicsBoard* OverlayGraphicsBoard::getLatestGraphicsBoard()
{
	auto size = graphics_boards_.size();
	if (size > 0)
	{
		return graphics_boards_[size - 1];
	}
}

//
GraphicsBoardTool::GraphicsBoardTool() :graphics_board_(nullptr), last_draw_rate_(0.0f)
{
}

GraphicsBoardTool::~GraphicsBoardTool()
{
	ClearRenders();
	graphics_board_->release();
	for (int i = 0, cnt = render_sprites_.size(); i < cnt; ++i)
	{
		auto sprite = render_sprites_[i];
		sprite->release();
	}
}

bool GraphicsBoardTool::Init(GraphicsBoard* graphics_board)
{
	CC_ASSERT(graphics_board);
	ClearRenders();
	graphics_board_ = graphics_board;
	graphics_board_->retain();
	return true;
}

void GraphicsBoardTool::PushRender()
{
	auto tex = new Texture2D();
	tex->initWithImage(graphics_board_->render_texture()->newCCImage(true));
	tex->autorelease();
	auto last_sprite = Sprite::createWithTexture(tex);
	CC_ASSERT(last_sprite);
	last_sprite->retain();
	render_sprites_.push_back(last_sprite);
}

void GraphicsBoardTool::PopRender()
{
	auto size = render_sprites_.size();
	if (size > 0)
	{
		auto last_sprite = render_sprites_[size - 1];
		CC_ASSERT(last_sprite);
		graphics_board_->ReplaceDisplay(last_sprite);
		render_sprites_.erase(render_sprites_.begin() + (size - 1));
		last_sprite->autorelease();
	}
}

void GraphicsBoardTool::ClearRenders(bool is_clear_board)
{
	for (int i = 0, cnt = render_sprites_.size(); i < cnt; ++i)
	{
		auto sprite = render_sprites_[i];
		sprite->release();
	}
	render_sprites_.clear();
	if (is_clear_board)
	{
		graphics_board_->ClearRenderTexture();
	}
}

float GraphicsBoardTool::CountDrawRate()
{
	return last_draw_rate_;


	auto size = graphics_board_->render_texture()->getSprite()->getContentSize();
	auto rt = RenderTexture::create(size.width, size.height, Texture2D::PixelFormat::RGBA8888);
	rt->begin();
	graphics_board_->native_sprite()->visit();
	rt->end();
	Director::getInstance()->getRenderer()->render();
	auto img_native = rt->newImage();
	auto img_draw = graphics_board_->render_texture()->newImage();
	auto native_data = img_native->getData();
	CC_ASSERT(native_data);
	auto draw_data = img_draw->getData();
	CC_ASSERT(draw_data);
	int count = 0;
	int sum = 0;
	int native_w = img_native->getWidth();
	int native_h = img_native->getHeight();
	int draw_w = img_draw->getWidth();
	int draw_h = img_draw->getHeight();
	for (int w = 0; w < native_w; ++w)
	{
		for (int h = 0; h < native_h; ++h)
		{
			Color4B native_color;
			native_color.r = *(native_data++);
			native_color.g = *(native_data++);
			native_color.b = *(native_data++);
			native_color.a = *(native_data++);

			Color4B draw_color;
			draw_color.r = *(draw_data++);
			draw_color.g = *(draw_data++);
			draw_color.b = *(draw_data++);
			draw_color.a = *(draw_data++);

			if (native_color.a > 0 && draw_color.a > 0)
			{
				count++;
			}
			sum++;
		}
	}
	last_draw_rate_ = (float)count / (float)sum;

	return last_draw_rate_;
}

const float GraphicsBoardTool::last_draw_rate() const
{
	return last_draw_rate_;
}

vector<Sprite*>& GraphicsBoardTool::render_sprites()
{
	return render_sprites_;
}

GraphicsBoardTool* GraphicsBoardTool::Create(GraphicsBoard* graphics_board)
{
	auto ref = new GraphicsBoardTool;
	if (ref && ref->Init(graphics_board))
	{
		ref->autorelease();
	}
	else
	{
		CC_SAFE_RELEASE(ref);
	}
	return ref;
}
