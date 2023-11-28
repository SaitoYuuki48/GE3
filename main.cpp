#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"

#include "SpriteCommon.h"
#include "Sprite.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    //ポインタ置き場
    Input* input_ = nullptr;
    WinApp* winApp_ = nullptr;
    DirectXCommon* dxCommon_ = nullptr;

    //WindowsAPIの初期化
    winApp_ = new WinApp();
    winApp_->Initialize();

    // DirectX初期化処理　ここから
    dxCommon_ = new DirectXCommon();
    dxCommon_->Initialize(winApp_);
    // DirectX初期化処理　ここまで

    //Input生成、初期化
    input_ = new Input();
    input_->Initialize(winApp_);

    //スプライトコモン
    SpriteCommon* spriteCommon = new SpriteCommon();
    spriteCommon->Initialize(dxCommon_);

    //スプライト
    Sprite* sprite = new Sprite();
    sprite->Initialize(dxCommon_,spriteCommon);

    // ゲームループ
    while (true) {
        if (winApp_->Update() == true) {
            break;
        }

        input_->Update();


       //更新前処理
        dxCommon_->PreDraw();

        sprite->Draw();

        //更新後処理
        dxCommon_->PostDraw();
    }

    delete sprite;
    delete spriteCommon;
    //解放処理
    delete input_;
    // DirectX解放
    delete dxCommon_;
    //WindowsAPI解放
    winApp_->Finalize();
    delete winApp_;

    return 0;
}
