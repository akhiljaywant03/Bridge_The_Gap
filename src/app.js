require('dotenv').config();
const express=require("express");
const app=express();
require("./db/conn");

const startupRegister=require("./models/startupRegisters");
const bcrypt=require("bcryptjs");
const port=process.env.PORT || 3000;
path=require('path')
app.use(express.static(path.join(__dirname,'../')+'public'));
app.use(express.urlencoded({extended:false}))

app.get("/",(req,res)=>{
    res.sendFile(path.join(__dirname,'../')+'home.html');
})

app.listen(port,()=>{
    console.log(path.join(__dirname,'../'));
})


app.get("/login",(req,res)=>{
    res.sendFile(path.join(__dirname,'../')+'login.html');
})

app.get("/option",(req,res)=>{
    res.sendFile(path.join(__dirname,'../')+'option.html');
})
app.get("/startup_form_main",(req,res)=>{
    res.sendFile(path.join(__dirname,'../')+'startup_form_main.html');
})
app.get("/investor_form",(req,res)=>{
    res.sendFile(path.join(__dirname,'../')+'investor_form_main.html');
})

app.get("/registerStartup",(req,res)=>{
    res.send("HI");
})


app.post("/registerStartup",async(req,res)=>{
    try{
        const password=req.body.password;
        const cpassword=req.body.confirmPassword;

        if(password===cpassword){
            const regStartup= new startupRegister({
                noOfFounders: req.body.founders,
                name: req.body.name,
                email: req.body.email,
                phone:req.body.phone,
                linkedIn:req.body.lurl,
                startupName:req.body.fname,
                startupStage:req.body.sstage,
                websiteAddress:req.body.website,
                startupDomain:req.body.domain,
                foundedIn:req.body.date,
                location:req.body.location,
                startupBusiness:req.body.btype,
                productSummary:req.body.productSumm,
                twitterPitch:req.body.twitter,
                teamSummary:req.body.team,
                difference:req.body.diff,
                cloud:req.body.cloudPlatform,
                amount:req.body.amountt,
                password:password,
                confirmPassword:cpassword

            }) 
            const token=await regStartup.generateAuthToken();

            const registered= await regStartup.save();
            res.status(201).send("Done");
            console.log("Done");
        }else{
            res.send("Passwords do not match");
        }
    }
    catch(error){
        res.status(400).send(error);
        console.log(error);
    }
})

app.get("/loginBoth",(req,res)=>{
    res.send("Hey");
})
app.post("/loginBoth",async(req,res)=>{
    try {
        const email=req.body.Email;
        const password=req.body.Password;
        const userEmail= await startupRegister.findOne({email:email});
        const isMatch=await bcrypt.compare(password,userEmail.password);
        const token=await userEmail.generateAuthToken();

        if(isMatch){
            res.status(201).send("Matched");
        }
        else{ 
            res.send("Email or password not matching");
        }
    } catch (error) {
        res.status(400).send(error);
        console.log(error);
        
    }

})