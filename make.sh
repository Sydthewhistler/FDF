rm exe
cc test.c minilibx_macos/libmlx.a -framework OpenGL -framework AppKit -DGL_SILENCE_DEPRECATION -o exe