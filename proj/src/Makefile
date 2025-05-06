# name of the program (Minix service)
PROG=proj

.PATH: ${.CURDIR}
.PATH: ${.CURDIR}/controllers
.PATH: ${.CURDIR}/controllers/keyboard_mouse
.PATH: ${.CURDIR}/controllers/timer
.PATH: ${.CURDIR}/controllers/graphics
.PATH: ${.CURDIR}/model/animSprite
.PATH: ${.CURDIR}/model/sprite
.PATH: ${.CURDIR}/model/bomb
.PATH: ${.CURDIR}/model/player
.PATH: ${.CURDIR}/model/wall
.PATH: ${.CURDIR}/images
.PATH: ${.CURDIR}/model/singleMode
.PATH: ${.CURDIR}/model/spriteLoader
.PATH: ${.CURDIR}/model/cursor
.PATH: ${.CURDIR}/model/explosion
.PATH: ${.CURDIR}/model/menu

# source code files
SRCS = 	main.c kbc.c kbd.c mouse.c timer.c utils.c graphics.c animatedSprite.c sprite.c bomb.c player.c wall.c singleMode.c spriteLoader.c cursor.c explosion.c menu.c

# additional compilation flags
CFLAGS += -pedantic -D_LCOM_OPTIMIZED_

CFLAGS += -pedantic -D_LCOM_OPTIMIZED_ \
          -I${.CURDIR}/controllers \
          -I${.CURDIR}/controllers/keyboard_mouse \
          -I${.CURDIR}/controllers/timer \
          -I${.CURDIR}/controllers/graphics \
          -I${.CURDIR}/model/animSprite \
          -I${.CURDIR}/model/sprite \
          -I${.CURDIR}/model/bomb \
          -I${.CURDIR}/model/player \
          -I${.CURDIR}/model/wall \
          -I${.CURDIR}/images \
          -I${.CURDIR}/model/singleMode \
          -I${.CURDIR}/model/spriteLoader \
          -I${.CURDIR}/model/cursor \
          -I${.CURDIR}/model/explosion \
          -I${.CURDIR}/model/menu \


# list of library dependencies
DPADD += ${LIBLCF}
LDADD += -llcf -lxpm -llm

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>