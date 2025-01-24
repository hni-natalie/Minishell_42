**Git Command**

Pull the latest code 

Always fetch the latest changes from the remote repo before creating a new branch

      git pull origin main
Create a branch 

      git branch <branch_name>
Switch to the branch

      git checkout <branch_name>
Work on your changes

      git add .
      git commit -m "created a new branch"
      git push origin <branch_name>
  List all the branches in the repo

        git branch -r
        
  Current branch will be highlighted with an asterisk (*)

      git branch 

Remove branch

      git branch -d <branch_name>
