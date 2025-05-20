日本語 / [English](README_EN.md)

# AEVE-Plugins

## 概要

アニメ制作向け Adobe AfterEffects
プラグイン「[F's Plugins](https://github.com/bryful/F-s-PluginsProjects)」
の高速化・モダン化実装です。\
【🚧現在進行中🚧】

## ダウンロード

最新版は [GitHubのReleaseページ](https://github.com/Hashory/AEVE-Plugins/releases) からダウンロードできます。

## TODOs

- [x] UTF-8化
- [ ] clang-formatの適用
- [ ] clang-tidyの適用
- [x] CMake化([after_effects_cmake](https://github.com/mobile-bungalow/after_effects_cmake)を参考にさせていただきました。一部完了していない箇所については[#1](https://github.com/Hashory/AEVE-Plugins/pull/1#issue-3075971090)を参照してください。)
- [ ] ドキュメントの作成
- [ ] Github Actions の作成
- [ ] MacOSの対応
- [ ] OpenFXの対応
- [ ] ソースコードの高速化・モダン化 → [機能別更新リスト](#機能別更新リスト)

### 機能別更新リスト

- ❌ 未着手
- 🟡 進行中
- ✅ 完了

| 機能名                  | 高速化・モダン化 |
| :---------------------- | :--------------: |
| AlphaFix                |        ❌        |
| AlphaThreshold          |        ❌        |
| AnimatedNoise           |        ❌        |
| CCplus                  |        ❌        |
| CellGrad                |        ❌        |
| ChannelBlur             |        ❌        |
| ChannelNoise            |        ❌        |
| ChannelShift            |        ❌        |
| ChromaticAberration     |        ❌        |
| ColorChange             |        ❌        |
| ColorChangeFromPoint    |        ❌        |
| ColorChangeSimple       |        ❌        |
| ColorKey                |        ❌        |
| ColorMatKey             |        ❌        |
| colorThreshold          |        ❌        |
| CreateAlpha             |        ❌        |
| EdgeBlur                |        ❌        |
| EdgeLine                |        ❌        |
| EdgeLine-Hi             |        ❌        |
| ExpsColors              |        ❌        |
| ExpsPos                 |        ❌        |
| Extract_Edge            |        ❌        |
| Extract-Hi              |        ❌        |
| FillColor               |        ❌        |
| Filter                  |        ❌        |
| Flare                   |        ❌        |
| Frame                   |        ❌        |
| FsLibrary               |        ❌        |
| FsLibrary_next          |        ❌        |
| FsSSFrame               |        ❌        |
| Grad_Test               |        ❌        |
| grayToColorize          |        ❌        |
| grayToCountourLine      |        ❌        |
| graytoneToColorize      |        ❌        |
| grayToWaveLine          |        ❌        |
| GuideFrame              |        ❌        |
| HLS_Reverse             |        ❌        |
| IroTore                 |        ❌        |
| IroToreAdjacent         |        ❌        |
| LineDetection           |        ❌        |
| LineTrace               |        ❌        |
| MainLineRepaint         |        ❌        |
| MainLineRepaint_old     |        ❌        |
| MaskFromRGB             |        ❌        |
| MaskFromRGB_Multi       |        ❌        |
| Max                     |        ❌        |
| Max_Kasumi              |        ❌        |
| Mosaic                  |        ❌        |
| NamiGarasu              |        ❌        |
| NFsLibrary              |        ❌        |
| NFsSkelton              |        ❌        |
| NoiseHiLo_Alpha         |        ❌        |
| NoiseHiLo_RGB           |        ❌        |
| OpticalDiffusion        |        ❌        |
| outAEX                  |        ❌        |
| OutLine                 |        ❌        |
| Paint                   |        ❌        |
| PaintMultPoint          |        ❌        |
| PaperPlaneGetWeight     |        ❌        |
| PaperPlaneGetWeightInfo |        ❌        |
| PixelExtend             |        ❌        |
| PixelReplace            |        ❌        |
| PixelSelector           |        ❌        |
| PluginSkeleton          |        ❌        |
| Posterization8bit       |        ❌        |
| Premultiply             |        ❌        |
| RandomLineNoise         |        ❌        |
| RandomMosaic            |        ❌        |
| RandomMosaic2nd         |        ❌        |
| RandomShift             |        ❌        |
| RGBAControl             |        ❌        |
| RgbToAlpha              |        ❌        |
| Scanline                |        ❌        |
| ScreenShakeDir          |        ❌        |
| ScreenShakeMM           |        ❌        |
| SelectColor             |        ❌        |
| SelectedBlur            |        ❌        |
| Shine                   |        ❌        |
| ShineParallel           |        ❌        |
| ShitsuKanBlur           |        ❌        |
| smokeThreshold          |        ❌        |
| Spark                   |        ❌        |
| Spark_Test              |        ❌        |
| SparkGrand              |        ❌        |
| SparkMult               |        ❌        |
| SparkRing               |        ❌        |
| SparkStorm              |        ❌        |
| sputteringAlpha         |        ❌        |
| sputteringCircle        |        ❌        |
| sputteringRect          |        ❌        |
| sputteringSplash        |        ❌        |
| Star                    |        ❌        |
| Star_Colorful           |        ❌        |
| Thin                    |        ❌        |
| ToGray                  |        ❌        |
| Tone                    |        ❌        |
| Toner                   |        ❌        |
| TouchDraw               |        ❌        |
| TouchDrawCenter         |        ❌        |
| TouchDrawStraght        |        ❌        |
| Unmult_KNSW_Fake        |        ❌        |
| Unmult_RG_Fake          |        ❌        |
| UsedColorList           |        ❌        |
| VideoGrid               |        ❌        |
| VideoLine               |        ❌        |
| VideoLine2nd            |        ❌        |
| whiteInOut              |        ❌        |
| YuvControl              |        ❌        |

## ライセンス

このソフトウェアはMITライセンスの下で公開されています。詳細は[LICENSE](LICENSE)をご覧ください。

## Super Thanks

「F's
Plugins」の作成者である[bry-ful](https://github.com/bryful)さんに感謝いたします。

- bry-fulさんの[Amazonのほしいものリスト](https://www.amazon.co.jp/hz/wishlist/ls/2ME5VSS8WJOX8?ref_=wl_sha)
