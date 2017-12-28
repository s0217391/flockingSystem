pipeline {
   agent any

    stages {
        stage('Build'){
            steps {
                build job: 'wipark_make', parameters: [string(name: 'BRANCH', value: params.branch)]
            }
        }
       
       stage('Flash'){
            steps {
                build job: 'wipark_flash'
            }
        }
    }
}
