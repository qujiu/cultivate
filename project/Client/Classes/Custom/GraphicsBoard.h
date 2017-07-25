#ifndef __GRAPHICS_BOARD_H__
#define __GRAPHICS_BOARD_H__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

enum EGraphicsBoardMode
{
	EGraphicsBoardMode_Null = -1,
	EGraphicsBoardMode_Color,
	EGraphicsBoardMode_ColorWithPalette,
	EGraphicsBoardMode_ColorWithStencil,
	EGraphicsBoardMode_Stencil,
	EGraphicsBoardMode_EraserWithPalette,
	EGraphicsBoardMode_OverlayStencil,

	EGraphicsBoardMode_Max
};

class GraphicsBoard : public cocos2d::Node
{
public:

	GraphicsBoard();
	~GraphicsBoard();

	bool InitWithFile(const Rect& rect, const char* graphics_file_path, const Color4B& color);
	bool InitWithFile(const char* native_file_path, const char* graphics_file_path, const EGraphicsBoardMode& mode, const Color4B& color, const bool bFlippedX);
	bool InitWithFile(Sprite* native, Sprite* graphics, const EGraphicsBoardMode& mode, const Color4B& color, const bool bFlippedX = false);

	void listenBackToForeground(Object *obj);
	void listenEnterToBackground(Object *obj);

	virtual void setPosition(const Vec2& pos);
	virtual void setAnchorPoint(const Vec2& anchorPoint);
	RenderTexture* render_texture();

	Sprite* native_sprite();
	Sprite* graphics_sprite();
	const Size& graphics_board_size() const;
	void CopyFrom(const GraphicsBoard* temple);

	void SetShader(const EGraphicsBoardMode& mode);
	void SetBrush(Sprite* brush = nullptr, const Color4B& color = ccc4(255, 255, 255, 255));
	void SetEraser(Sprite* eraser = nullptr, bool is_show_palette = false);
	void BrushClick(const Vec2& pos);
	void BrushMove(const Vec2& start, const Vec2& end);
	void BrushMoveIntelligent(const Vec2& start, const Vec2& end);
	void BrushMoveIntelligentUpdate(float delta);
	bool IsBrushIntelligentDone();
	void ClearRenderTexture();
	void ClearRenderTextureSlowly(float time = .5f);
	void ClearRenderScheduleCallback(float delta);
	void ReplaceDisplay(Sprite* dst);

	void SaveBlendTex();

	static GraphicsBoard* Create(const Rect& rect, const char* graphics_file_path, const Color4B& color);
	static GraphicsBoard* Create(const char* native_file_path, const char* graphics_file_path, const EGraphicsBoardMode& mode, const Color4B& color = ccc4(255, 255, 255, 255), const bool bFlippedX = false);
	static GraphicsBoard* Create();

private:
	void renderBrushBefore();
	void renderBrush(Sprite* brush, const Vec2& pos);
	void renderBrushAfter();

private:
	Sprite* native_sprite_;
	Sprite* brush_sprite_;
	RenderTexture* render_texture_;
	float clear_alpha_;
	float clear_duration_;
	vector<Sprite*> burshes_;
	vector<Vec4> brush_pos_array_;
	EGraphicsBoardMode use_shader_mode_;
	//std::function<void()> clear_callback_func_;
};
class OverlayGraphicsBoard : public cocos2d::Node
{
public:
	OverlayGraphicsBoard();
	~OverlayGraphicsBoard();

	bool Init(const char* native_file_path, const char* graphics_file_path, const Color4B& color, const bool bFlippedX);

	bool IsCurrentNative(const std::string& native_file_path);
	GraphicsBoard* ChangeGraphicsBoard(const char* native_file_path, const char* graphics_file_path, const Color4B& color = ccc4(255, 255, 255, 255), const bool bFlippedX = false);
	GraphicsBoard* ChangeGraphicsBoardNull();
	void ChangeGraphicsBoard(const char* graphics_file_path, const Color4B& color = ccc4(255, 255, 255, 255));
	void ClearGraphicsBoards();
	void ClearGraphicsBoardsSlowly();
	void BrushClick(const Vec2& pos);
	void BrushMove(const Vec2& start, const Vec2& end);
	void SetBrush(Sprite* brush = nullptr, const Color4B& color = ccc4(255, 255, 255, 255));
	void SetEraser(Sprite* eraser = nullptr, bool is_show_palette = false);
	void CopyFrom(const OverlayGraphicsBoard* temple);

	static OverlayGraphicsBoard* Create(const char* native_file_path, const char* graphics_file_path, const Color4B& color = ccc4(255, 255, 255, 255), const bool bFlippedX = false);

	void EraserMove(const Vec2& start, const Vec2& end);

	GraphicsBoard* getLatestGraphicsBoard();

private:
	vector<GraphicsBoard*> graphics_boards_;
	std::string current_native_file_path_;
};

class GraphicsBoardTool : public cocos2d::Ref
{
public:
	GraphicsBoardTool();
	~GraphicsBoardTool();

	bool Init(GraphicsBoard* graphics_board);

	void PushRender();
	void PopRender();
	void ClearRenders(bool is_clear_board = false);
	float CountDrawRate();
	const float last_draw_rate() const;
	vector<Sprite*>& render_sprites();

	static GraphicsBoardTool* Create(GraphicsBoard* graphics_board);

private:
	GraphicsBoard* graphics_board_;
	vector<Sprite*> render_sprites_;
	float last_draw_rate_;
};

#endif 