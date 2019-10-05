.name "sti"
.comment "coucou"

# ld		150, r3
 sti		r1, %0, %0 # ok ( ! verifier le carry ! )
# sti		r1, 100, %100 # ok
# sti		r1, 100, %1 # ok
# sti		r1, 10, %0 # ok
 sti		r1, 0, %0 # ok
# sti		r1, 0, %1 # ok
# sti		r1, 0, %10 # ok
# sti		r1, 0, %100 # ok
# sti		r1, 100, %0 # FAUX ( offset fausse )
# sti		r1, 10, %0 # FAUX ( offset fausse )
# sti		r1, 0, %0 # FAUX ( offset fausse )

# ok donc la tu vas pas chercher la valeur a l'offset 1000
# mais tu prends la valeur 1000.
# si ya pas le % ton param->size == 2, il devrait etre egal a 4, non ?
# sinon, faut rajouter un 'char type' dans ton t_param...

# sti		r1, r3, %15 # OK
# sti		r1, r1, r3 # FAUX ( offset fausse )
# sti		r1, %20, %15 # OK
# sti		r1, %20, r1 # OK
# sti		r1, -10, %-50 # FAUX (offset fausse )
# sti		r1, -20, r1 # FAUX (offset fausse )


# xD voila pour les tests
# t'arrives a compiler sous linux ?
# bah je compile avec ton term la / ? /
# je re, en pause

# vas y je vais manger dehors, on se voit demain.
# Zoub Zoub

# scandaleux
