# cpp-library
My algorithm library

git init 						// Inizializza
git remote add origin "url"				// Collega url repository e salvare alias origin
git remote -v						// Mostra url repository collegate
git remote remove "origin"				// Elimina dai link salvati

git clone "url"						// Creare una copia locale di un repository remoto (origin è associato all'url)
git pull						// Aggiorna progetto locale con online
git pull origin "tuo_branch"				// Aggiorna branch locale con online

git add .						// Aggiungi allo staging
git status						// Visualizza file aggiunti
git rm "nome_file"

git branch "nome_del_branch"				// Crea branch separato
git switch "nome_del_branch"				// Switchare branch
git merge "branch_di_origine"				// Merge 2 branch
git branch						// Visualizza branch
git branch -m "vecchio_nome_branch" "nuovo_nome_branch"	// Rinomina branch


git commit -m "commento"				// Salvataggio in locale
git commit -a -m "commento"				// Add all + salvataggio in locale
git log							// Lista commit con hash
git commit --amend					// Modifica ultimo commit
git diff "hash_commit1" "hash_commit2"			// Confronta due commit

git push origin master					// Carica su git 
git push -u origin master				// Carica su git collegando la repository remota con alias origin con ramo master 
git push						// Carica su git tutti i commit
git push origin "hash_del_commit"			// Carica su git solo il commit selezionato