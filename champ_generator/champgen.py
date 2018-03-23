import random

def main(stdscr):
    curses.curs_set(False)
    gameOver = False
    c = 0

    # cree l'environnement
    env = Env(stdscr)
    env.display()

    while c != ord('q'):
        c = stdscr.getch()

        if not gameOver:
            # fait jouer le joueur
            env.checkInput(c)

            # fait jouer les monstres
            env.finishTurn()

            # affichage
            env.display()

            # verifie que le jeu n'est pas fini
            if (env.player.dead):
                gameOver = True
        else:
            # affiche game over
            n = len(env.map)
            m = len(env.map[0])
            stdscr.addstr(n//2, m//2-5, 'GAME OVER !')



if __name__ == "__main__":
    inst = ["live", "ld", "st", "add",
            "sub", "and", "or", "xor",
            "zjmp", "ldi", "sti", "fork",
            "lld", "lldi", "lfork", "aff"]
    print(inst)
