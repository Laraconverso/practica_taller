# Hands On Git

Este repositorio esta para poner en práctica algunos conceptos y
funciones de Git.

Por si Git te es totalmente extraño, Git es un sistema de
control de versions que mantiene registro de
los cambios hechos sobre uno o varios archivos.

Este hands-on es para jugar un poco con algunos conceptos de Git pero
no pretende ser una guia completa.

## Donde estoy?

Git implementa el concepto de ramas (branches) para representar líneas
de desarrollo.

Podes ver en todo momento en que branch estas con

```shell
$ git status
```

Y podes moverte de un branch a otro con

```shell
$ git checkout main
```

O con

```shell
$ git switch main
```

## Qué es un commit?

En Git los cambios sobre el repositorio son llamados *commits* y un branch
entonces es una secuencia de commits que representa una línea de
desarrollo.

Cambia al branch `good-quality-commits` con `git switch` y
mira el último commit del branch con `git log -1`

Veras q cada commit en Git tiene un *hash* único, algo de la forma
`60b4f8c652b45eddc52a77f0b306ddb79e2678c5`. Muchos comandos reciben un
hash como ese aunque es común usar solo los primeros dígitos.

Para ver un commit en detalle junto con el cambio que introdujo el
commit (lease, el diff) podes hacer `git show <hash>`.

## Commits de buena calidad

Con `git log` podes ver todos los commits del branch `good-quality-commits`
y con `git log --patch` podes verlos junto a sus diffs.

Notaras que estos commits tienen buenos mensajes descriptivos de cada
uno de los cambios agregados.

Trata de buscar en que commit se implementó la función `factorial`.

Podrías buscar commit por commit y ver el diff de cada uno de ellos
hasta ver cual commit implementó `factorial`.

Pero por suerte en el branch hay **buenos commits**: commits que tienen
buenos mensajes que explican no solo **que** cambio introducen sino
también el **por que**.

Con `git log` podrás entonces simplemente **leer los mensajes** de los
commits y no tendrás que revisar los diffs.

Proba ahora en ver en que commit se *fixeo* el buffer overflow.

Una vez mas podrás usar `git log` pero he aquí un truquillo: con `git
log --grep=<text>` podes buscar los commits que tenga `<text>` en sus
mensajes.

Como los commits son de buena calidad es muy probable que el commit que
fixea el buffer overflow **diga** que lo fixea (y probablemente diga el
**por que**).

Combinalo con `--patch` para ver el mensaje y el diff.

## Commits de baja calidad

Pasemos ahora al branch `poor-quality-commits` con `git switch`
(verifica que estas en ese branch con `git status` y cual es su último
commit con `git log -1`.

Notaras el peculiar y poco descriptivo mensaje de ese commit.

He aquí un challenge: busca en este branch en que commit se implementó
`factorial`.

Veras que ni `git log` ni `git log --grep` te servirán ya que todos los
commits tienen un **muy pobre** mensaje que **no explican** nada.

Por suerte aun te queda una carta bajo la manga. `git log -G<text>
--patch` va buscar `<text>` no en los mensajes sino en los diffs.

Probá entonces `git log -Gfactorial --patch`. No te salvarás de
revisar varios diffs pero al menos no tendrás que revisar absolutamente
todos.

He aquí entonces algo que no se estresa lo suficiente: invertir 2
minutos para **escribir commits de buena calidad da sus frutos**.

## Buscando el bug

La documentación del
proyecto (`doctests/factorial.md`) funciona no solo como documentación sino
también como tests automáticos.

[byexample](https://byexamples.github.io) es una tool que toma los
snippets de código de la documentación (los ejemplos), los ejecuta y
compara la salida con lo que el ejemplo muestra.

Si la comparación falla habrás encontrado un bug.

Para poder correr los tests necesitas tener Python 3 instalado y `pip`.
En Debian/Ubuntu podes hacer `apt-get install python3 python3-pip`.
Luego instalate `byexample` corriendo `pip install byexample`.

Asegúrate que estas en el branch `poor-quality-commits` y
corre `make tests` para ver que solo uno de los tests falla (cual?).

Al parecer hay un factorial que no esta bien calculado...

Podrías ponerte a debuggear, si, pero tal vez podemos usar Git a nuestro
favor.

Esta es la idea: en algún momento todos los tests pasaban, luego alguien
introdujo el bug y a partir de ahí los tests quedaron rotos.

Si es así podríamos ir commit a commit del branch `poor-quality-commits` y
correr en cada paso `make tests`: en el momento que los tests dejen de
fallar (o empiecen a fallar) ya sabras que **ese commit** metió el bug.

Tal vez no te diga exactamente cual es el bug pero tendrás **mucho mas
contexto** (lo que ayuda muchísimo al debugging)

Ahora, ir de a un commit a la vez es una búsqueda secuencial y ya sabras
que hay algo mucho mejor: búsqueda binaria y Git ya la implementa por vos
con `git bisect`!

Corre estos 2 comandos para iniciar el `bisect mode` y marcar el commit
actual como *"malo"*.

```shell
git bisect start
git bisect bad
```

Ahora, con este comando le decís a Git que commit es el *"bueno"*.

```shell
git bisect good <hash>
```

En `<hash>` tenes que poner el hash de algún commit que sepas que los
tests pasaban. Por suerte hay un commit así. Fijate con `git log` q hay
un commit que dice `"arreglo bug, vamos que los tests pasan!!"`, usa el
hash de ese commit.

A partir de acá Git te va a switchear al commit punto medio entre el
*"bueno"* y el *"malo"*.

Lo que tenes que hacer es correr `make tests` y si los tests pasan
marcas el commit como bueno (`git bisect good`) o de lo contrario como
malo (`git bisect bad`).

Así Git sabe cual es el siguiente commit medio y te hace el switch.
Continuas así hasta encontrar el commit que introdujo el bug.

Cuando termines tenes que hacer `git bisect reset` para limpiar todo el
estado de Git.

## Diferencias entre branches

Cuando trabajas en equipo es útil ver que cambios están en un branch
respecto a otro.

Típicamente vas a querer comparar que features/fixes un branch `foo`
esta a punto de introducir al branch `main` haciendo `git log
main..foo` o `git diff main foo`.

Con `git log main..foo` ves que commits están en `foo` pero no aun en
`main` mientras con `git diff main foo` ves que cambios (patch) `foo`
agregaría a `main`.

Proba en ver que cambios hay entre `poor-quality-commits` y
`good-quality-commits` con `git diff poor-quality-commits
good-quality-commits`.

Podes ver el cambio hecho en la función `factorial` que hace que anden
los tests en `good-quality-commits` pero no en `poor-quality-commits` ?

Podes ayudarte viendo solo los cambios sobre `factorial/main.cpp`
corriendo `git diff poor-quality-commits good-quality-commits --
factorial/main.cpp`.


## Quien fue?

Es correcto `if (num <= 1)` o debería ser `if (num == 0)` ?

No es raro a veces ver un código sospechoso y preguntarse, quien lo
escribió y por que?

A veces la respuesta explica y el código sospechoso deja de serlo. Otras
veces uno termina encontrando un bug.

Cuando queremos ver que commit introdujo una linea de código en
particular podemos usar `git blame`. (`git log -G` serviría también pero
hay veces que `git log -G` es demasiado impreciso).

Anda al branch `good-quality-commits` y corre `git blame
factorial/main.cpp`. Que commit metió ese `if (num <= 1)` tan sospechoso?

Gracias a que el commit es de buena calidad podrás saber entonces el **por
que si el código es correcto o no**.

## Hooks

Git soporta una serie de *hooks*, scripts a ejecutarse en distintas
etapas del versionado.

[pre-commit](https://pre-commit.com) es una administrador de hooks que
te permite instalar y correrlos fácilmente.

Necesitas tener Python 3 y `pip`. Luego corre `pip install pre-commit`.

Andate al branch `good-quality-commits` e instala los hooks corriendo:

```
pre-commit install
pre-commit install --hook-type commit-msg
```

El branch `good-quality-commits` fue agregando y configurando varios hooks:
`cpplint`, `cppcheck` y `commitizen`.

Para `cppcheck` necesitas tener el programa `cppcheck` instalado. Podes
tenerlo corriendo `apt-get install cppcheck`.

Proba en modificar `factorial/main.cpp` dejando alguna variable sin
definir o sin usar.

Hace

```
git add factorial/main.cpp
git commit
```

Si commiteas debería `cppcheck` correr automáticamente y fallarte el commit.

Si commiteas con algún mensaje poco descriptivo, debería ser
`commitizen` quien te falle.

Puede parecerte tedioso pero pensalo, al detectar rápido algo que esta
mal, es mucho mas fácil arreglarlo ahí, en el momento, en vez de
arreglarlo 2 semanas después.

## Editor

Si corres `git commit` te abrirá un editor por default, típicamente
`nano`, `emacs` o `vim`.

Puede que te tientes y hagas `git commit -m "mi mensaje aqui"` que es
más fácil.

**No.**

Usar `git commit -m "mi mensaje aqui"` solo lleva a que hagas commits de
baja calidad.

Si el editor por default que abre Git no te gusta, cambialo!!

Aquí Google is your friend.


## Conclusiones

Como *"usar"* Git esta [super documentado](https://git-scm.com/book/en/v2)
pero no  es fácil ver por que deberíamos usar Git en principio.

Por que deberíamos hacer commits pequeños? Por que deberíamos escribir
buenos mensajes de commit? Para que sirve todo eso?

Este hands-on espera haberte mostrado las razones. Commits pequeños con
buenos mensajes que expliquen el qué y el por qué permiten:

 - rápida inspección del diff con `git show` o `git log --patch`
 - rápido entendimiento de la intension (el por que) cuando hacemos un
`git blame`
 - encontrar diferencia entre branches con `git log main..foo` y `git
diff main foo`
 - encontrar el commit que habla de `X` con `git log --grep` y `git log
-G`
 - encontrar el commit que introdujo un error con `git bisect`

No trates de memorizarte algo. Es altamente probable que la próxima semana
ya no recuerdes estos comandos y para cuando los necesites no lo usaras.

Te tentaras con usar aquello mas familiar. "Tenes un bug? 99% probable
que termines usando prints".

Vas a arreglar el bug, seguro. **Pero a que costo?**

`git blame` te hubiera ahorrado un par de horas y tiempo es lo que no le
sobra a nadie.

Armate un *cheatsheet* (aka, apunte) con lo visto en este onboarding.

Armalo en papel y pegalo en alguna pared.

