<!DOCTYPE html>
<html lang="ja">
<head>
<style>
	h1 {
        font-weight: 900;
        font-size: xx-large;
    }
    p {
        color:blue;
        line-height:1.5;
    }
</style>
</head>

# LaTeXで回路図を書きたい

## 前書き

### きっかけ

LaTeXで回路図を書きたいって思って調べても，日本語の記事がほとんど見つからず，英語のマニュアルを読む羽目になったからこの記事を書くことにした．
画像埋め込み(`\includegraphics{}`)でも構わないが，LaTeXで完結させたかった為，この手法を用いた．

正直な話，おすすめはできない(面倒くさい)．

### 注意点

基本座標指定なので，事前に座標を考えておかないと，きれいな回路図を作ることが難しい．

## パッケージ

```tex
\usepackage[RPvoltages]{circuitikz}
```

オプションのRPvoltagesが無いと，直列電源の向きが逆になってしまう．
交流電源のみ使用する場合や，気にしない場合は不要．

また，

```tex
\usepackage[dvipdfmx]{graphix}
```

も必要である．
これが無いと回路図が一切出力されないので注意が必要である．

## RC直列回路例

## ソースコード

以下のソースコードをコンパイルする際は，

```tex
\usepackage{here}
\usepackage{siunitx}
```

を用いること．

hereパッケージは，tex出力内の位置固定，siunitxパッケージは単位等を入れる時に有用な役割である．

[$\LaTeX$ソース]()

出力


## 成果物

## 以前お世話になったサイト様

* 

